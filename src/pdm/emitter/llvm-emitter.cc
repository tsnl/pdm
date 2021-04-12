#include "llvm-emitter.hh"

#include <iostream>

#include <filesystem>
#include <fstream>
#include <vector>
#include <stack>
#include <map>

#include "pdm/ast/stmt/vax.hh"
#include "pdm/types/type.hh"
#include "pdm/printer/printer.hh"

#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>


namespace pdm::emitter {

    struct Dim {
        DimKind dim_kind;

        // for each dim, two values are guaranteed to exist on the stack:
        // 1. 'storage' (accessed by loading llvm_ptr_to_storage): the space for data of the user type.
        // 2. for only Global_Fn: 'ptr_to_storage' actually contains the value of the function
        union {
            LLVMValueRef llvm_ptr_to_storage;
            LLVMValueRef llvm_fn_ptr;
        } data_as;
        LLVMTypeRef llvm_storage_type;
    };

    DimKind dim_kind(Dim* dim) {
        return dim->dim_kind;
    }

}

namespace pdm::emitter {

    LLVMModuleRef emit_llvm_for_package(Compiler *compiler, ast::Package *package);
    LLVMModuleRef emit_llvm_for_script(Compiler *compiler, ast::Script *script);

    LLVMModuleRef new_llvm_module_for(ast::ISourceNode* source_node);
    LLVMTypeRef emit_llvm_type_for(types::Type* type);

}

namespace pdm::emitter {

    bool emit_llvm(Compiler *compiler_with_loaded_sources) {
        auto ok = true;
        auto compiler = compiler_with_loaded_sources;

        bool dump_llvm_ir_to_files = true;
        std::vector<LLVMModuleRef> llvm_modules;
        for (auto source_node: compiler->all_source_nodes()) {
            auto source_path = source_node->source()->abs_path();

            // selecting a target path & emitting LLVM IR:
            std::filesystem::path target_path;
            LLVMModuleRef llvm_module;
            {
                switch (source_node->kind()) {
                    case ast::Kind::Package: {
                        // emit an LLVM IR module parallel to the `pd-index.json` file.
                        // i.e. `pd-index.ll`
                        target_path = source_node->source()->abs_path() / "pd-index.ll";
                        llvm_module = emit_llvm_for_package(
                            compiler,
                            dynamic_cast<ast::Package *>(source_node)
                        );
                        break;
                    }
                    case ast::Kind::Script: {
                        // emit an LLVM IR module parallel to the `*.pd` file.
                        // i.e. `*.ll`
                        target_path = source_path;
                        target_path.replace_extension(".ll");
                        llvm_module = emit_llvm_for_script(compiler, dynamic_cast<ast::Script *>(source_node));
                        break;
                    }
                    default: {
                        assert(0 && "Unknown ast::Kind for ISourceNode");
                    }
                }
            }
            assert(llvm_module && "Failed to emit an LLVM module despite passing all prior compiler phases.");
            assert(!target_path.empty() && "Invalid LLVM IR output path.");

            // Emitting LLVM file at `target_path`:
            // std::cout << "Emitting LLVM file at " << target_path << std::endl;
            if (dump_llvm_ir_to_files) {
                char *error_message = nullptr;
                LLVMPrintModuleToFile(llvm_module, target_path.c_str(), &error_message);
                if (error_message) {
                    std::cout << "Failed to write LLVM IR to file: " << error_message << std::endl;
                } else {
                    std::cout << "Wrote LLVM IR file to: " << target_path << std::endl;
                }
            }
        }

        return ok;
    }

}

namespace pdm::emitter {

    LLVMModuleRef new_llvm_module_for(ast::ISourceNode *source_node) {
        auto module_id_string = source_node->source()->abs_path_string();
        auto module = LLVMModuleCreateWithName(module_id_string.c_str());
        source_node->x_llvm_module_ref(module);
        return module;
    }

    LLVMTypeRef emit_llvm_type_for(types::Type* type) {
        int const POINTER_ADDRESS_SPACE = 0;

        auto char_type = LLVMInt32Type();

        std::vector<LLVMTypeRef> element_types{2};
        element_types[0] = LLVMInt64Type();
        element_types[1] = LLVMPointerType(char_type, POINTER_ADDRESS_SPACE);
        auto string_type = LLVMStructType(element_types.data(), element_types.size(), true);

        switch (type->type_kind()) {
            case types::Kind::Void: {
                return LLVMVoidType();
            }
            case types::Kind::String: {
                return string_type;
            }
            case types::Kind::UnsignedInt:
            case types::Kind::SignedInt: {
                auto width_in_bits = dynamic_cast<types::IntType*>(type)->width_in_bits();
                return LLVMIntType(width_in_bits);
            }
            case types::Kind::Float: {
                auto width_in_bits = dynamic_cast<types::FloatType*>(type)->width_in_bits();
                switch (width_in_bits)
                {
                    case 16: return LLVMHalfType();
                    case 32: return LLVMFloatType();
                    case 64: return LLVMDoubleType();
                    default: {
                        assert(0 && "Unknown floating point target size.");
                    }
                }
            }
            case types::Kind::Enum: {
                assert(0 && "NotImplemented: emitting LLVM types for enums");
            }
            case types::Kind::Struct: {
                assert(0 && "NotImplemented: emitting LLVM types for structs");
            }
            case types::Kind::Fn: {
                auto fn_type = dynamic_cast<types::FnType*>(type);
                std::vector<types::FnType::ArgInfo> raw_param_types_vec = fn_type->args();

                // converting arguments into LLVM:
                size_t num_args = raw_param_types_vec.size();
                std::vector<LLVMTypeRef> param_types_vec{num_args};
                for (size_t i = 0; i < raw_param_types_vec.size(); i++) {
                    auto arg_info = raw_param_types_vec[i];

                    // The 'user type' refers to the type of data the user expects to pass
                    // in and out of this parameter.
                    // For 'out' and 'inout' parameters, pointers to the user type are passed **to functions/operators**
                    // under the hood.
                    // This conversion is made here for function signatures:
                    auto user_type = emit_llvm_type_for(arg_info.type);
                    switch (arg_info.access_spec) {
                        case ast::VArgAccessSpec::InOut:
                        case ast::VArgAccessSpec::Out: {
                            param_types_vec[i] = LLVMPointerType(user_type, 0);
                            break;
                        }
                        case ast::VArgAccessSpec::In: {
                            param_types_vec[i] = user_type;
                            break;
                        }
                    }
                }

                auto return_type = emit_llvm_type_for(fn_type->return_type());
                auto llvm_type = LLVMFunctionType(return_type, param_types_vec.data(), param_types_vec.size(), false);
                return llvm_type;
            }
            default: {
                assert(0 && "NotImplemented: `emit_llvm_type_for` for TypeKind ?");
            }
        }
    }

}

namespace pdm::emitter {

    LLVMModuleRef emit_llvm_for_package(Compiler *compiler, ast::Package *package) {
        auto module = new_llvm_module_for(package);

        // todo: populate this module.


        return module;
    }
}

namespace pdm::emitter {

    class BaseScriptVisitor: public ast::TinyVisitor {
      protected:
        Compiler* m_compiler;
        ast::ISourceNode* m_source_node;
        LLVMModuleRef m_output_module;

      protected:
        BaseScriptVisitor(
            Compiler* compiler,
            ast::ISourceNode* source_node,
            LLVMModuleRef output_module
        );
    };

    inline BaseScriptVisitor::BaseScriptVisitor(
        Compiler* compiler,
        ast::ISourceNode* source_node,
        LLVMModuleRef output_module
    )
    :   ast::TinyVisitor(),
        m_compiler(compiler), m_source_node(source_node), m_output_module(output_module)
    {}

    //
    // Emitting headers:
    // Everything GLOBAL and STATIC is emitted during the header.
    //

    class EmitHeadersVisitor: public BaseScriptVisitor {
      private:
        static std::string const s_root_module_name;
        static std::string const s_module_name_separator;

      private:
        // this stack stores the WHOLE module prefix to use, e.g.
        // module_a, module_a:home, module_a:home:cfg
        std::vector<std::string> m_module_prefix_stack;

      public:
        EmitHeadersVisitor(
            Compiler* compiler,
            ast::ISourceNode* source_node,
            LLVMModuleRef output_module
        );

      public:
        [[nodiscard]] bool on_visit_script(ast::Script* script, VisitOrder visit_order) override;
        [[nodiscard]] bool on_visit_lambda_exp(ast::LambdaExp* lambda_exp, VisitOrder) override;
        [[nodiscard]] bool on_visit_script_field(ast::Script::Field* field, VisitOrder visit_order) override;
        [[nodiscard]] bool on_visit_value_mod_field(ast::NativeModExp::ValueField* node, VisitOrder visit_order) override;
        [[nodiscard]] bool on_visit_type_mod_field(ast::NativeModExp::TypeField* node, VisitOrder visit_order) override;
        [[nodiscard]] bool on_visit_class_mod_field(ast::NativeModExp::ClassField* node, VisitOrder visit_order) override;
        [[nodiscard]] bool on_visit_mod_mod_field(ast::NativeModExp::ModuleField* node, VisitOrder visit_order) override;
        [[nodiscard]] bool on_visit_string_exp(ast::StringExp *node, VisitOrder visit_order) override;

      private:
        void push_module_name(intern::String name);
        void pop_module_name();

      private:
        void emit_preamble();
        void emit_postamble();
    };

    std::string const EmitHeadersVisitor::s_root_module_name = "root";
    std::string const EmitHeadersVisitor::s_module_name_separator = "_$_";

    EmitHeadersVisitor::EmitHeadersVisitor(
        Compiler* compiler,
        ast::ISourceNode* source_node,
        LLVMModuleRef output_module
    )
    : BaseScriptVisitor(compiler, source_node, output_module),
      m_module_prefix_stack(1, s_root_module_name)
    {}

    void EmitHeadersVisitor::push_module_name(intern::String mod_name) {
        std::string module_prefix = (
            m_module_prefix_stack.back() +
            s_module_name_separator +
            mod_name.cpp_str()
        );
        m_module_prefix_stack.push_back(module_prefix);
    }
    void EmitHeadersVisitor::pop_module_name() {
        m_module_prefix_stack.pop_back();
    }

    void EmitHeadersVisitor::emit_preamble() {}

    void EmitHeadersVisitor::emit_postamble() {}

    bool EmitHeadersVisitor::on_visit_script(ast::Script* script, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            emit_preamble();
        } else if (visit_order == VisitOrder::Post) {
            emit_postamble();
        }
        return true;
    }

    bool EmitHeadersVisitor::on_visit_lambda_exp(ast::LambdaExp* lambda_exp, VisitOrder) {
        // NOTE:
        // -  @me I KNOW YOU WILL WASTE TIME ON THIS SO HEED THIS ADVICE
        // - for now, this visitor does nothing since...
        //   1. every lambda is either top-level or within another function
        //   2. closures are not yet supported
        //   3. => all lambdas are top-level lambdas
        //   4. => all lambdas are emitted by the
        //      field (so they can be mapped to a global name and linked against other modules)
        // - so WHEN CLOSURES ARE ADDED...
        //   1. add 2 lambda_exp properties to check if it was...
        //       1. expanded from a sugared lambda
        //       2. if it was assigned to a module level symbol
        //       3. Note (1) => (2), but (2) =/=> (1), so must be stored independently
        // - if not assigned as top-level,
        //   THEN DO THIS HERE:
        //      1. generate closures
        //          - every 'Defn' stores an 'fn' ptr where it was defined
        //          - if a looked up symbol does not have 'fn' ptr same as current top 'fn', it is closed over.
        //      2. emit an anonymous function with a strange (non-conflicting/rare) name
        //      3. set ->x_llvm_fn appropriately
        //      4. ensure it is emitted by `emit_ro_llvm_value...`
        return true;
    }

    bool EmitHeadersVisitor::on_visit_script_field(ast::Script::Field* field, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            push_module_name(field->name());
            return true;
        } else if (visit_order == VisitOrder::Post) {
            pop_module_name();
            return true;
        } else {
            assert(0 && "NotImplemented: unknown visit order");
            return false;
        }
    }

    bool EmitHeadersVisitor::on_visit_value_mod_field(ast::NativeModExp::ValueField* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            std::string emit_name = (
                m_module_prefix_stack.back() +
                s_module_name_separator +
                node->name().cpp_str()
            );
            intern::String emit_name_int_str = emit_name;
            types::Type* global_type = node->rhs_exp()->x_type_of_var()->get_type_soln();

            if (node->rhs_exp()->kind() == ast::Kind::LambdaExp) {
                // defining a function
                auto lambda_node = dynamic_cast<ast::LambdaExp*>(node->rhs_exp());
                assert(lambda_node && "Expected Lambda RHS based on 'Kind'");

                auto fn_type = dynamic_cast<types::FnType*>(global_type);
                assert(fn_type && "Expected 'soln' type after typer for 'lambda-exp' in 'EmitHeaders'");
                LLVMTypeRef llvm_fn_type = emit_llvm_type_for(fn_type);
                LLVMValueRef llvm_fn = LLVMAddFunction(m_output_module, emit_name.c_str(), llvm_fn_type);

                auto dim = new Dim{};
                dim->dim_kind = DimKind::Global_Fn;
                dim->data_as.llvm_fn_ptr = llvm_fn;
                dim->llvm_storage_type = llvm_fn_type;
                node->x_defn()->x_llvm_dim(dim);
            } else {
                // defining a global variable with an initializer
                LLVMTypeRef llvm_global_type = emit_llvm_type_for(global_type);
                LLVMValueRef llvm_global_ptr = LLVMAddGlobal(
                    m_output_module,
                    llvm_global_type,
                    emit_name.c_str()
                );

                // defining a 'dim' with the correct info:
                auto new_dim = new Dim{};
                new_dim->dim_kind = DimKind::Global_Val;
                new_dim->data_as.llvm_ptr_to_storage = llvm_global_ptr;
                new_dim->llvm_storage_type = llvm_global_type;
                node->x_defn()->x_llvm_dim(new_dim);
            }
        } else if (visit_order == VisitOrder::Post) {
            // do nothing
        }
        return true;
    }

    bool EmitHeadersVisitor::on_visit_type_mod_field(ast::NativeModExp::TypeField* node, VisitOrder visit_order) {
        // emit nothing
        return true;
    }
    bool EmitHeadersVisitor::on_visit_class_mod_field(ast::NativeModExp::ClassField* node, VisitOrder visit_order) {
        // emit nothing
        return true;
    }
    bool EmitHeadersVisitor::on_visit_mod_mod_field(ast::NativeModExp::ModuleField* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Pre) {
            push_module_name(node->name());
        } else if (visit_order == VisitOrder::Post) {
            pop_module_name();
        }
        return true;
    }

    bool EmitHeadersVisitor::on_visit_string_exp(ast::StringExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            std::stringstream initializer_string_stream;
            for (auto const& piece: node->pieces()) {
                initializer_string_stream << static_cast<char const*>(piece.content().const_data());
            }
            std::string initializer_content = initializer_string_stream.str();
            LLVMValueRef llvm_literal_initializer = LLVMConstString(
                reinterpret_cast<char const*>(initializer_content.data()),
                initializer_content.size(),
                false   // opt to null-terminate for backward-compatibility with C.
            );
            std::string llvm_literal_global_name = "string-literal @ " + node->loc().cpp_str();
            LLVMValueRef llvm_literal_global = LLVMAddGlobal(
                m_output_module,
                LLVMTypeOf(llvm_literal_initializer),
                llvm_literal_global_name.c_str()
            );
            LLVMSetInitializer(llvm_literal_global, llvm_literal_initializer);
            LLVMSetLinkage(llvm_literal_global, LLVMInternalLinkage);
            LLVMSetGlobalConstant(llvm_literal_global, true);

            node->x_llvm_global(llvm_literal_global);
        }
        return true;
    }

}

namespace pdm::emitter {

    //
    // Emitting module defs: 3 parts
    // 1. RValues
    // 2. LValues
    // 3. EmitDefsVisitor
    //    - emitting things only in basic blocks
    //

    enum class LValueKind;
    class LValue;
    class IdLValue;
    class TupleLValue;

    enum class RValueKind;
    class RValue;

    // L-Values: read + write

    enum class LValueKind {
        Id,
        Tuple
    };

    class LValue {
        LValueKind m_kind;
        ast::Exp* m_exp;

      protected:
        inline explicit
        LValue(LValueKind kind, ast::Exp* exp)
        :   m_kind(kind),
            m_exp(exp)
        {}

        virtual ~LValue() = default;

      public:
        [[nodiscard]]
        inline
        LValueKind l_value_kind() const {
            return m_kind;
        }

        [[nodiscard]]
        inline
        ast::Exp* exp() const {
            return m_exp;
        }
    };

    class IdLValue: public LValue {
        Dim* m_dim;

      public:
        inline explicit
        IdLValue(ast::Exp* exp, Dim* dim)
        :   LValue(LValueKind::Id, exp),
            m_dim(dim)
        {}

      public:
        [[nodiscard]]
        inline
        LLVMValueRef llvm_storage_ptr() const {
            return m_dim->data_as.llvm_ptr_to_storage;
        }
    };

    class TupleLValue: public LValue {
        std::vector<LValue*> m_l_value_vec;

      public:
        inline explicit
        TupleLValue(ast::Exp* exp, std::vector<LValue*>&& l_value_vec)
        : LValue(LValueKind::Tuple, exp),
          m_l_value_vec(std::move(l_value_vec))
        {}

      public:
        [[nodiscard]]
        inline
        std::vector<LValue*> const& ptr_vec() const {
            return m_l_value_vec;
        }
    };


    // R-Values: read-only values
    class RValue {
        LLVMValueRef m_llvm_value;
        LLVMValueRef m_opt_llvm_stack_ptr;
        ast::Exp* m_exp;

      public:
        inline
        RValue(ast::Exp* exp, LLVMValueRef llvm_value, LLVMValueRef llvm_stack_ptr = nullptr)
        : m_llvm_value(llvm_value),
          m_opt_llvm_stack_ptr(llvm_stack_ptr),
          m_exp(exp)
        {}

      public:
        [[nodiscard]]
        LLVMValueRef llvm_value() const {
            return m_llvm_value;
        }

        [[nodiscard]]
        LLVMValueRef opt_llvm_stack_ptr() const {
            return m_opt_llvm_stack_ptr;
        }

        [[nodiscard]]
        ast::Exp* exp() const {
            return m_exp;
        }
    };

    // EmitDefsVisitor: ties together prior emitters to emit defs for a **script**, headers already generated.

    class EmitDefsVisitor: public BaseScriptVisitor {
      public:
        struct Frame {
            LLVMValueRef anonymous_fn;
            LLVMBasicBlockRef last_bb;
            ast::LambdaExp* defn_lambda_exp;
        };

      private:
        void fn_push(ast::LambdaExp* node, LLVMValueRef anonymous_llvm_header_fn);
        Dim* fn_dim(DimKind, intern::String name, types::Type* content_type);
        void fn_pop();

      private:
        void fn_aux_on_top_frame_chg();

      private:
        Compiler* m_compiler;
        std::vector<Frame*> m_fn_stack;

      public:
        EmitDefsVisitor(
            Compiler* compiler,
            ast::ISourceNode* source_node,
            LLVMModuleRef output_module
        );

        bool fn_emit(ast::LambdaExp* lambda_node, LLVMValueRef llvm_fn);

      public:
        [[nodiscard]] bool on_visit_value_mod_field(ast::NativeModExp::ValueField* node, VisitOrder visit_order) override;

      public:
        [[nodiscard]] RValue* emit_ro_llvm_value_for(ast::Exp* exp);
        [[nodiscard]] LValue* emit_rw_llvm_value_for(ast::Exp* exp);

      public:
        void help_assign_exp_to_l_value(LValue* lhs, ast::Exp* rhs);
    };

    inline EmitDefsVisitor::EmitDefsVisitor(
        Compiler* compiler,
        ast::ISourceNode* source_node,
        LLVMModuleRef output_module
    )
    :   BaseScriptVisitor(compiler, source_node, output_module),
        m_compiler(compiler),
        m_fn_stack()
    {
        auto new_frame = new Frame{}; {
            new_frame->anonymous_fn = nullptr;
            new_frame->last_bb = nullptr;
            new_frame->defn_lambda_exp = nullptr;
        }
        m_fn_stack.push_back(new_frame);
    }

    bool EmitDefsVisitor::on_visit_value_mod_field(ast::NativeModExp::ValueField* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            if (node->rhs_exp()->kind() == ast::Kind::LambdaExp) {
                // emitting the function body:
                auto lambda_exp = dynamic_cast<ast::LambdaExp*>(node->rhs_exp());
                auto llvm_fn_ptr = node->x_defn()->x_llvm_dim()->data_as.llvm_fn_ptr;
                if (!fn_emit(lambda_exp, llvm_fn_ptr)) {
                    return false;
                }
            }
        }
        return true;
    }

    void EmitDefsVisitor::fn_push(ast::LambdaExp* node, LLVMValueRef anonymous_llvm_header_fn) {
        auto frame = new Frame{};
        frame->anonymous_fn = anonymous_llvm_header_fn;
        frame->last_bb = nullptr;
        frame->defn_lambda_exp = node;
        // `frame->symbols` is default-initialized.

        // pushing to the stack:
        m_fn_stack.push_back(frame);
        fn_aux_on_top_frame_chg();
    }

    Dim* EmitDefsVisitor::fn_dim(DimKind dim_kind, intern::String name, types::Type* content_type) {
        assert(!m_fn_stack.empty() && "Cannot invoke `fn_dim` before `fn_push`");
        Frame* top_frame = m_fn_stack.back();

        // identifying the type of storage:
        LLVMTypeRef dim_storage_type = emit_llvm_type_for(content_type);

        // pushing memory to the stack for this argument:
        // - Arg_InOut, Arg_Out do not push any memory to the stack at all; we already have a ptr from an argument.
        // - for Arg_In (non-reference), we push memory and copy the argument into it (relying on LLVM optimization) so
        //   we have a local stack ptr and can generalize all our code.
        //   - the alternative is a 'get_value' function that checks what kind of value there is, loads from a pointer,
        //     and then returns
        // - only Val and Var do push memory to the stack.
        // - NOTE: if the caller dims arguments, they must set `llvm_ptr_to_storage` themselves.
        LLVMValueRef dim_storage_ptr = nullptr;
        switch (dim_kind) {
            case DimKind::Global_Fn:
            case DimKind::Global_Val:
            case DimKind::Arg_InOut:
            case DimKind::Arg_Out: {
                // do nothing!
                break;
            }
            case DimKind::Arg_In:
            case DimKind::Var:
            case DimKind::Val: {
                // allocate space:
                std::string dim_kind_string = ([dim_kind] () {
                    switch (dim_kind) {
                        case DimKind::Arg_In: return "arg-in";
                        case DimKind::Arg_Out: return "arg-out";
                        case DimKind::Arg_InOut: return "arg-inout";
                        case DimKind::Var: return "var";
                        case DimKind::Val: return "val";
                        case DimKind::Global_Val: return "global-val";
                        case DimKind::Global_Fn: return "global-fn";
                    }
                }());
                std::string dim_name = "dim-ptr[" + dim_kind_string + "]:" + name.cpp_str();
                // assert(true_dim_type && "BUG: expected `actual_dim_content` != nullptr");
                dim_storage_ptr = LLVMBuildAlloca(
                    static_cast<LLVMBuilderRef>(m_compiler->llvm_builder()),
                    dim_storage_type,
                    dim_name.c_str()
                );
            }
        }

        auto dim = new Dim{}; {
            dim->dim_kind = dim_kind;
            dim->data_as.llvm_ptr_to_storage = dim_storage_ptr;
            dim->llvm_storage_type = dim_storage_type;
        }

        return dim;
    }

    void EmitDefsVisitor::fn_pop() {
        assert(!m_fn_stack.empty() && "Cannot invoke `fn_pop` before `fn_push`");
        m_fn_stack.pop_back();

        fn_aux_on_top_frame_chg();
    }

    void EmitDefsVisitor::fn_aux_on_top_frame_chg() {
        if (!m_fn_stack.empty()) {
            Frame* top_frame = m_fn_stack.back();

            if (top_frame->anonymous_fn && top_frame->last_bb == nullptr) {
                top_frame->last_bb = LLVMAppendBasicBlock(top_frame->anonymous_fn, "fn_entry_point");
            }

            LLVMPositionBuilderAtEnd(static_cast<LLVMBuilderRef>(m_compiler->llvm_builder()), top_frame->last_bb);
        } else {
            LLVMClearInsertionPosition(static_cast<LLVMBuilderRef>(m_compiler->llvm_builder()));
        }
    }

    bool EmitDefsVisitor::fn_emit(ast::LambdaExp* lambda_node, LLVMValueRef llvm_fn) {
        // creating a basic block for an entry point:
        fn_push(lambda_node, llvm_fn);

        // alloca-ing space for each argument if required:
        std::vector<ast::VPattern::Field*> const& fields = lambda_node->lhs_vpattern()->fields();
        for (size_t arg_index = 0; arg_index < fields.size(); arg_index++) {

            // 'dim'-ing (pushing) memory on the stack for this argument:
            ast::VPattern::Field* arg_field = fields[arg_index];
            DimKind dim_kind = ([arg_field] () {
                switch (arg_field->accepted_varg_kind()) {
                    case ast::VArgAccessSpec::In: return DimKind::Arg_In;
                    case ast::VArgAccessSpec::Out: return DimKind::Arg_Out;
                    case ast::VArgAccessSpec::InOut: return DimKind::Arg_InOut;
                    default: {
                        assert(0 && "Invalid dim_kind in formal arg.");
                    }
                }
            }());
            Dim* dim = fn_dim(dim_kind, arg_field->lhs_name(), arg_field->x_defn_tv()->get_type_soln());
            assert(dim && "Failed to 'dim' for fn-arg.");
            arg_field->x_defn()->x_llvm_dim(dim);

            // storing the argument into this stack variable:
            switch (arg_field->accepted_varg_kind()) {
                case ast::VArgAccessSpec::In: {
                    // 'in' arguments have space pushed just like 'val' or 'var'
                    // here, we store (copy) the value in the argument to the stack, relying on mem2reg to optimize
                    // if required.
                    assert(
                        dim->data_as.llvm_ptr_to_storage &&
                        "expected non-nullptr to storage after fn_dim for Arg_In."
                    );
                    LLVMValueRef init_store_value = LLVMGetParam(llvm_fn, arg_index);
                    LLVMBuildStore(
                        static_cast<LLVMBuilderRef>(
                            m_compiler->llvm_builder()
                        ),
                        init_store_value,
                        dim->data_as.llvm_ptr_to_storage
                    );
                    break;
                }
                case ast::VArgAccessSpec::Out:
                case ast::VArgAccessSpec::InOut: {
                    // 'ref' arguments do not occupy any stack space.
                    // instead, the pointer is the argument itself.
                    assert(
                        dim->data_as.llvm_ptr_to_storage == nullptr &&
                        "expected nullptr to storage after fn_dim for ref arg"
                    );
                    LLVMValueRef llvm_ptr_to_storage = LLVMGetParam(llvm_fn, arg_index);
                    dim->data_as.llvm_ptr_to_storage = llvm_ptr_to_storage;
                    break;
                }
            }
        }


        // emitting the body, then a return instruction:
        // NOTE:
        //  even if we return void, must still emit the function body because
        //  there may be side-effects.
        // NOTE:
        //   'void' expressions return a 'nullptr' handle when emitting.

        // body:
        RValue* llvm_return_value = emit_ro_llvm_value_for(lambda_node->rhs_body());

        // return instruction:
        types::Type* return_type = lambda_node->x_type_of_var()->get_type_soln();
        if (return_type->type_kind() == types::Kind::Void) {
            assert(
                llvm_return_value != nullptr &&
                "LlvmEmitter: expected nullptr llvm_return_value for void return"
            );
            LLVMBuildRetVoid(static_cast<LLVMBuilderRef>(m_compiler->llvm_builder()));
        } else {
            assert(
                llvm_return_value != nullptr &&
                "LlvmEmitter: expected non-nullptr llvm_return_value for non-void return"
            );
            LLVMBuildRet(static_cast<LLVMBuilderRef>(m_compiler->llvm_builder()), llvm_return_value->llvm_value());
        }

        // popping the frame
        fn_pop();
        return true;
    }

    RValue* EmitDefsVisitor::emit_ro_llvm_value_for(ast::Exp* exp) {
        auto builder = static_cast<LLVMBuilderRef>(m_compiler->llvm_builder());

        types::Type* exp_type = exp->x_type_of_var()->get_type_soln();

        // pattern-matching to emit values:
        switch (exp->kind()) {
            case ast::Kind::UnitExp: {
                return new RValue(exp, nullptr);
            }
            case ast::Kind::IntExp: {
                auto int_exp = dynamic_cast<ast::IntExp*>(exp);
                auto int_type = dynamic_cast<types::IntType*>(exp_type);
                assert(int_exp && int_type && "Incorrect datatypes in int-exp.");
                return new RValue(exp, LLVMConstInt(
                    emit_llvm_type_for(exp_type),
                    int_exp->value(),
                    int_type->using_sign_ext()
                ));
            }
            case ast::Kind::FloatExp: {
                auto float_exp = dynamic_cast<ast::FloatExp*>(exp);
                assert(float_exp && "Incorrect datatypes in float-exp.");
                return new RValue(exp, LLVMConstReal(
                    emit_llvm_type_for(exp_type),
                    static_cast<double>(float_exp->value())
                ));
                break;
            }
            case ast::Kind::IdExp: {
                auto id_exp = dynamic_cast<ast::IdExp*>(exp);
                auto id_type = exp_type;
                if (id_type->type_kind() != types::Kind::Void) {
                    Dim* dim = id_exp->x_defn()->x_llvm_dim();
                    assert(dim && "Could not emit LLVM IR for ID: `x_llvm_dim` unset.");

                    switch (dim->dim_kind) {
                        case DimKind::Global_Fn: {
                            // no load required: just access the value directly.
                            return new RValue(
                                exp,
                                dim->data_as.llvm_fn_ptr
                            );
                        }
                        case DimKind::Global_Val:
                        case DimKind::Arg_In:
                        case DimKind::Arg_InOut:
                        case DimKind::Var:
                        case DimKind::Val: {
                            // loading from the pointer:
                            std::string id_name = "loaded:" + id_exp->name().cpp_str();
                            return new RValue(
                                exp,
                                LLVMBuildLoad(
                                    builder,
                                    dim->data_as.llvm_ptr_to_storage,
                                    id_name.c_str()
                                ),
                                dim->data_as.llvm_ptr_to_storage
                            );
                            break;
                        }
                        case DimKind::Arg_Out: {
                            // not allowed
                            assert(0 && "NotImplemented: report 'cannot read from Arg_Out'");
                            break;
                        }
                    }
                } else {
                    return new RValue(
                        exp,
                        nullptr
                    );
                }
            }
//            case ast::Kind::StringExp: {
//                break;
//            }
            case ast::Kind::UnaryExp: {
                assert(0 && "NotImplemented: emitting unary operators");

                auto unary_exp = dynamic_cast<ast::UnaryExp*>(exp);
                auto unary_op = unary_exp->unary_operator();

                switch (unary_op) {
                    case ast::UnaryOperator::Plus: {
                        break;
                    }
                    case ast::UnaryOperator::Minus: {
                        break;
                    }
                    case ast::UnaryOperator::Not: {
                        break;
                    }
                    case ast::UnaryOperator::META_Count: {
                        break;
                    }
                }

                break;
            }
            case ast::Kind::BinaryExp: {
                auto binary_exp = dynamic_cast<ast::BinaryExp*>(exp);
                auto binary_op = binary_exp->binary_operator();

                auto ret_type = binary_exp->x_type_of_var()->get_type_soln();
                assert(ret_type && "`ret_type` is nullptr");
                auto llvm_ret_type = emit_llvm_type_for(ret_type);

                // depending on the return type, we must cast arguments to the right type

                auto lhs_exp = binary_exp->lhs_operand();
                auto rhs_exp = binary_exp->rhs_operand();

                auto lhs_exp_type = lhs_exp->x_type_of_var()->get_type_soln();
                auto rhs_exp_type = rhs_exp->x_type_of_var()->get_type_soln();

                auto llvm_lhs_exp_type = emit_llvm_type_for(lhs_exp_type);
                auto llvm_rhs_exp_type = emit_llvm_type_for(rhs_exp_type);

                RValue* emitted_lhs_operand = emit_ro_llvm_value_for(lhs_exp);
                RValue* emitted_rhs_operand = emit_ro_llvm_value_for(rhs_exp);

                LLVMValueRef llvm_lhs = emitted_lhs_operand->llvm_value();
                LLVMValueRef llvm_rhs = emitted_rhs_operand->llvm_value();

                // trying to emit builtin inline definitions:
                // - if successful, return immediately with result
                {
                    assert(
                        lhs_exp_type->type_kind() == rhs_exp_type->type_kind() &&
                        "Asymmetric type kinds in type system"
                    );
                    types::Kind symmetric_type_kind = lhs_exp_type->type_kind();

                    // todo: implement type conversions as required.
                    if (lhs_exp_type != rhs_exp_type) {
                        // this should be moved to a function and reused for function calls
                        switch (symmetric_type_kind) {
                            case types::Kind::SignedInt: {
                                auto lhs_type = dynamic_cast<types::IntType*>(lhs_exp_type);
                                auto rhs_type = dynamic_cast<types::IntType*>(rhs_exp_type);

                                // extending the smaller value to match the bigger value:
                                // may update either `llvm_lhs` or `llvm_rhs`
                                if (lhs_type->width_in_bits() > rhs_type->width_in_bits()) {
                                    llvm_rhs = LLVMBuildSExtOrBitCast(builder, llvm_rhs, llvm_lhs_exp_type, "converted(s-ext)_rhs");
                                    llvm_rhs_exp_type = llvm_lhs_exp_type;
                                } else if (lhs_type->width_in_bits() < rhs_type->width_in_bits()) {
                                    llvm_lhs = LLVMBuildSExtOrBitCast(builder, llvm_lhs, llvm_rhs_exp_type, "converted(s-ext)_lhs");
                                    llvm_lhs_exp_type = llvm_rhs_exp_type;
                                } else {
                                    assert(0 && "Error: apparently equal types have different pointer reps.");
                                }
                                break;
                            }
                            case types::Kind::UnsignedInt: {
                                auto lhs_type = dynamic_cast<types::IntType*>(lhs_exp_type);
                                auto rhs_type = dynamic_cast<types::IntType*>(rhs_exp_type);

                                // extending the smaller value to match the bigger value:
                                // may update either `llvm_lhs` or `llvm_rhs`
                                if (lhs_type->width_in_bits() > rhs_type->width_in_bits()) {
                                    llvm_rhs = LLVMBuildZExt(builder, llvm_rhs, llvm_lhs_exp_type, "converted(u-ext)_rhs");
                                    llvm_rhs_exp_type = llvm_lhs_exp_type;
                                } else if (lhs_type->width_in_bits() < rhs_type->width_in_bits()) {
                                    llvm_lhs = LLVMBuildZExt(builder, llvm_lhs, llvm_rhs_exp_type, "converted(u-ext)_lhs");
                                    llvm_lhs_exp_type = llvm_rhs_exp_type;
                                } else {
                                    assert(0 && "Error: apparently equal types have different pointer reps.");
                                }
                                break;
                            }
                            case types::Kind::Float: {
                                auto lhs_type = dynamic_cast<types::FloatType*>(lhs_exp_type);
                                auto rhs_type = dynamic_cast<types::FloatType*>(rhs_exp_type);

                                // extending the smaller value to match the bigger value:
                                // may update either `llvm_lhs` or `llvm_rhs`
                                if (lhs_type->width_in_bits() > rhs_type->width_in_bits()) {
                                    llvm_rhs = LLVMBuildFPExt(builder, llvm_rhs, llvm_lhs_exp_type, "converted(fp-ext)_rhs");
                                    llvm_rhs_exp_type = llvm_lhs_exp_type;
                                } else if (lhs_type->width_in_bits() < rhs_type->width_in_bits()) {
                                    llvm_lhs = LLVMBuildFPExt(builder, llvm_lhs, llvm_rhs_exp_type, "converted(fp-ext)_lhs");
                                    llvm_lhs_exp_type = llvm_rhs_exp_type;
                                } else {
                                    assert(0 && "Error: apparently equal types have different pointer reps.");
                                }
                                break;
                            }
                            default: {
                                break;
                            }
                        }
                    }
                    // - for each operator, can acquire a 'convert-to-type' in _typer_ ('t' metavar)

                    // there are several binary operators to apply to 3 type kinds with 3-6 types each.
                    switch (binary_op) {
                        // these 4 operators are defined for every prime type.
                        case ast::BinaryOperator::Mul: {
                            switch (symmetric_type_kind) {
                                case types::Kind::Float:
                                    return new RValue(exp, LLVMBuildFMul(builder, llvm_lhs, llvm_rhs, "f_mul_res"));
                                case types::Kind::UnsignedInt:
                                case types::Kind::SignedInt:
                                    return new RValue(exp, LLVMBuildMul(builder, llvm_lhs, llvm_rhs, "i_mul_res"));
                                default: {}
                            }
                            break;
                        }
                        case ast::BinaryOperator::Div: {
                            switch (symmetric_type_kind) {
                                case types::Kind::Float:
                                    return new RValue(exp, LLVMBuildFDiv(builder, llvm_lhs, llvm_rhs, "f_div_res"));
                                case types::Kind::SignedInt:
                                    return new RValue(exp, LLVMBuildSDiv(builder, llvm_lhs, llvm_rhs, "s_div_res"));
                                case types::Kind::UnsignedInt:
                                    return new RValue(exp, LLVMBuildUDiv(builder, llvm_lhs, llvm_rhs, "u_div_res"));
                                default: {}
                            }
                            break;
                        }
                        case ast::BinaryOperator::Rem: {
                            switch (symmetric_type_kind) {
                                case types::Kind::Float:
                                    return new RValue(exp, LLVMBuildFRem(builder, llvm_lhs, llvm_rhs, "f_rem_res"));
                                case types::Kind::SignedInt:
                                    return new RValue(exp, LLVMBuildSRem(builder, llvm_lhs, llvm_rhs, "s_rem_res"));
                                case types::Kind::UnsignedInt:
                                    return new RValue(exp, LLVMBuildURem(builder, llvm_lhs, llvm_rhs, "u_rem_res"));
                                default: {}
                            }
                        }
                        case ast::BinaryOperator::Add: {
                            switch (symmetric_type_kind) {
                                case types::Kind::Float:
                                    return new RValue(exp, LLVMBuildFAdd(builder, llvm_lhs, llvm_rhs, "f_add_res"));
                                case types::Kind::SignedInt:
                                case types::Kind::UnsignedInt:
                                    return new RValue(exp, LLVMBuildAdd(builder, llvm_lhs, llvm_rhs, "i_add_res"));
                                default: {}
                            }
                        }
                        case ast::BinaryOperator::Subtract: {
                            switch (symmetric_type_kind) {
                                case types::Kind::Float:
                                    return new RValue(exp, LLVMBuildFSub(builder, llvm_lhs, llvm_rhs, "f_subtract_res"));
                                case types::Kind::SignedInt:
                                case types::Kind::UnsignedInt:
                                    return new RValue(exp, LLVMBuildSub(builder, llvm_lhs, llvm_rhs, "i_subtract_res"));
                                default: {}
                            }
                        }
                        case ast::BinaryOperator::Less: {
                            switch (symmetric_type_kind) {
                                case types::Kind::Float:
                                    return new RValue(exp, LLVMBuildFCmp(builder, LLVMRealOLT, llvm_lhs, llvm_rhs, "f_less_than_res"));
                                case types::Kind::SignedInt:
                                    return new RValue(exp, LLVMBuildICmp(builder, LLVMIntSLT, llvm_lhs, llvm_rhs, "s_less_than_res"));
                                case types::Kind::UnsignedInt:
                                    return new RValue(exp, LLVMBuildICmp(builder, LLVMIntULT, llvm_lhs, llvm_rhs, "u_less_than_res"));
                                default: {}
                            }
                        }
                        case ast::BinaryOperator::Greater: {
                            switch (symmetric_type_kind) {
                                case types::Kind::Float:
                                    return new RValue(exp, LLVMBuildFCmp(builder, LLVMRealOGT, llvm_lhs, llvm_rhs, "f_greater_than_res"));
                                case types::Kind::SignedInt:
                                    return new RValue(exp, LLVMBuildICmp(builder, LLVMIntSGT, llvm_lhs, llvm_rhs, "s_greater_than_res"));
                                case types::Kind::UnsignedInt:
                                    return new RValue(exp, LLVMBuildICmp(builder, LLVMIntUGT, llvm_lhs, llvm_rhs, "u_greater_than_res"));
                                default: {}
                            }
                        }
                        case ast::BinaryOperator::LessOrEq: {
                            switch (symmetric_type_kind) {
                                case types::Kind::Float:
                                    return new RValue(exp, LLVMBuildFCmp(builder, LLVMRealOLE, llvm_lhs, llvm_rhs, "f_less_or_eq_res"));
                                case types::Kind::SignedInt:
                                    return new RValue(exp, LLVMBuildICmp(builder, LLVMIntSLE, llvm_lhs, llvm_rhs, "s_less_or_eq_res"));
                                case types::Kind::UnsignedInt:
                                    return new RValue(exp, LLVMBuildICmp(builder, LLVMIntULE, llvm_lhs, llvm_rhs, "u_less_or_eq_res"));
                                default: {}
                            }
                        }
                        case ast::BinaryOperator::GreaterOrEq: {
                            switch (symmetric_type_kind) {
                                case types::Kind::Float:
                                    return new RValue(exp, LLVMBuildFCmp(builder, LLVMRealOGE, llvm_lhs, llvm_rhs, "f_greater_or_eq_res"));
                                case types::Kind::SignedInt:
                                    return new RValue(exp, LLVMBuildICmp(builder, LLVMIntSGE, llvm_lhs, llvm_rhs, "s_greater_or_eq_res"));
                                case types::Kind::UnsignedInt:
                                    return new RValue(exp, LLVMBuildICmp(builder, LLVMIntUGE, llvm_lhs, llvm_rhs, "u_greater_or_eq_res"));
                                default: {}
                            }
                        }
                        case ast::BinaryOperator::Equals: {
                            switch (symmetric_type_kind) {
                                case types::Kind::Float:
                                    return new RValue(exp, LLVMBuildFCmp(builder, LLVMRealOEQ, llvm_lhs, llvm_rhs, "f_equals_res"));
                                case types::Kind::UnsignedInt:
                                case types::Kind::SignedInt:
                                    return new RValue(exp, LLVMBuildICmp(builder, LLVMIntEQ, llvm_lhs, llvm_rhs, "i_equals_res"));
                                default: {}
                            }
                        }
                        case ast::BinaryOperator::NotEquals: {
                            switch (symmetric_type_kind) {
                                case types::Kind::Float:
                                    return new RValue(exp, LLVMBuildFCmp(builder, LLVMRealONE, llvm_lhs, llvm_rhs, "f_not_equals_res"));
                                case types::Kind::SignedInt:
                                case types::Kind::UnsignedInt:
                                    return new RValue(exp, LLVMBuildICmp(builder, LLVMIntNE, llvm_lhs, llvm_rhs, "i_not_equals_res"));
                                default: {}
                            }
                        }
                        case ast::BinaryOperator::And: {
                            if (symmetric_type_kind == types::Kind::UnsignedInt) {
                                return new RValue(exp, LLVMBuildAnd(builder, llvm_lhs, llvm_rhs, "u_and"));
                            }
                        }
                        case ast::BinaryOperator::XOr: {
                            if (symmetric_type_kind == types::Kind::UnsignedInt) {
                                return new RValue(exp, LLVMBuildAnd(builder, llvm_lhs, llvm_rhs, "u_xor"));
                            }
                        }
                        case ast::BinaryOperator::Or: {
                            if (symmetric_type_kind == types::Kind::UnsignedInt) {
                                return new RValue(exp, LLVMBuildAnd(builder, llvm_lhs, llvm_rhs, "u_or"));
                            }
                        }
                        case ast::BinaryOperator::META_Count: {
                            assert(0 && "Invalid Binary Operator-- META_Count intended as a placeholder.");
                        }
                    }
                }
                // cont. BinaryExp

                // if this point is reached and no 'return' in this branch, undefined op
                assert(0 && "NotImplemented: reporting undefined BinaryOp for arguments of type ?.");
            }
//            case ast::Kind::LambdaExp: {
//                break;
//            }
//            case ast::Kind::IfExp: {
//                break;
//            }
            case ast::Kind::ModuleDotExp: {
                assert(0 && "NotImplemented: emitting LLVM for ModuleDotExp");
                break;
            }
            case ast::Kind::VCallExp: {
                auto call_exp = dynamic_cast<ast::VCallExp*>(exp);
                auto call_type = exp_type;

                // translating the called expression:
                auto llvm_lhs_called_exp = emit_ro_llvm_value_for(call_exp->lhs_called());
                auto fn_type = dynamic_cast<types::FnType*>(call_exp->lhs_called()->x_type_of_var()->get_type_soln());
                auto fn_formal_arg_info = fn_type->args();

                // translating the arguments, casting/converting if required:
                std::vector<LLVMValueRef> actual_args;
                actual_args.reserve(call_exp->args().size());
                size_t args_count = call_exp->args().size();
                for (size_t arg_index = 0; arg_index < args_count; arg_index++) {
                    ast::VArg* actual_arg = call_exp->args()[arg_index];

                    switch (actual_arg->access_spec()) {
                        case ast::VArgAccessSpec::In: {
                            RValue* actual_arg_r_value = emit_ro_llvm_value_for(actual_arg->arg_exp());

                            // whenever we call an operator, there is a chance the formal and actual type are not
                            // identical.
                            // when this happens, the emitter must cast/convert the actual value into another value
                            // of the formal type before passing it.

                            types::Type* formal_arg_type;
                            types::Type* actual_arg_type;
                            {
                                types::FnType::ArgInfo& formal_arg_info = fn_formal_arg_info[arg_index];
                                assert(
                                    formal_arg_info.access_spec == actual_arg->access_spec() &&
                                    "Typer error: mismatched access specifiers detected in call"
                                );
                                formal_arg_type = formal_arg_info.type;
                                actual_arg_type = actual_arg_r_value->exp()->x_type_of_var()->get_type_soln();
                            }

                            // performing type conversion if required:
                            LLVMValueRef converted_value = nullptr;
                            if (formal_arg_type == actual_arg_type) {
                                converted_value = actual_arg_r_value->llvm_value();
                            } else {
                                assert(0 && "NotImplemented: casting input arguments for fn call");
                            }
                            assert(converted_value && "Expected non-nullptr casted value to pass to fn call");
                            actual_args.push_back(converted_value);
                            break;
                        }
                        case ast::VArgAccessSpec::InOut:
                        case ast::VArgAccessSpec::Out: {
                            // note mutable values are always passed as pointers, which do not need to be cast.
                            LValue* actual_arg_l_value = emit_rw_llvm_value_for(actual_arg->arg_exp());
                            switch (actual_arg_l_value->l_value_kind()) {
                                case LValueKind::Id: {
                                    auto id_l_value = dynamic_cast<IdLValue*>(actual_arg_l_value);
                                    actual_args.push_back(id_l_value->llvm_storage_ptr());
                                    break;
                                }
                                case LValueKind::Tuple: {
                                    auto tuple_l_value = dynamic_cast<IdLValue*>(actual_arg_l_value);
                                    assert(0 && "NotImplemented: passing a tuple as an inout/out argument");
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }

                // building a call expression:
                // - NOTE: cannot specify a name because possible void return values will result in LLVM complaining
                //         that we cannot name 'void' values.
                std::string returned_value_name = "returned";
                LLVMValueRef returned_value = LLVMBuildCall(
                    builder,
                    llvm_lhs_called_exp->llvm_value(),
                    actual_args.data(), actual_args.size(),
                    ""
                );

                return new RValue(
                    call_exp,
                    returned_value
                );
            }
            case ast::Kind::ChainExp: {
                auto chain_exp = dynamic_cast<ast::ChainExp*>(exp);

                // emitting the chain prefix:
                for (auto stmt: chain_exp->prefix()) {
                    switch (stmt->kind()) {
                        case ast::Kind::VarStmt: {
                            auto vax_stmt = dynamic_cast<ast::VaxStmt*>(stmt);
                            assert(vax_stmt && "LlvmEmitter: Invalid 'var' stmt datatype in chain-exp.");

                            // evaluating the RHS exp:
                            auto rhs_value = emit_ro_llvm_value_for(vax_stmt->rhs_exp());

                            // storing into LHS variables:
                            if (vax_stmt->lhs_lpattern()->destructure()) {
                                assert(0 && "NotImplemented: emitting LLVM IR for de-structured lpatterns.");
                            } else {
                                ast::LPattern::Field* sole_field = vax_stmt->lhs_lpattern()->fields()[0];
                                assert(sole_field && "LlvmEmitter: nullptr field in lpattern");

                                auto sole_field_type = sole_field->x_defn_tv()->get_type_soln();
                                Dim* dim = fn_dim(
                                    DimKind::Var,
                                    sole_field->lhs_name(),
                                    sole_field_type
                                );
                                assert(dim && "LlvmEmitter: Failed to 'dim' for 'var' statement.");
                                sole_field->x_defn()->x_llvm_dim(dim);

                                LLVMBuildStore(
                                    builder,
                                    rhs_value->llvm_value(),
                                    dim->data_as.llvm_ptr_to_storage
                                );
                            }
                            break;
                        }
                        case ast::Kind::ValStmt: {
                            auto vax_stmt = dynamic_cast<ast::VaxStmt*>(stmt);
                            assert(vax_stmt && "Invalid 'vax' stmt datatype in chain-exp.");

                            // evaluating the RHS exp:
                            auto rhs_value = emit_ro_llvm_value_for(vax_stmt->rhs_exp());

                            // storing into LHS variables:
                            if (vax_stmt->lhs_lpattern()->destructure()) {
                                assert(0 && "NotImplemented: emitting LLVM IR for de-structured lpatterns.");
                            } else {
                                auto sole_field = vax_stmt->lhs_lpattern()->fields()[0];
                                assert(sole_field && "LlvmEmitter: nullptr field in lpattern");

                                auto sole_field_type = sole_field->x_defn_tv()->get_type_soln();
                                Dim* dim = fn_dim(
                                    DimKind::Val,
                                    sole_field->lhs_name(),
                                    sole_field_type
                                );
                                assert(dim && "LlvmEmitter: Failed to 'dim' for 'var' statement.");
                                sole_field->x_defn()->x_llvm_dim(dim);

                                LLVMBuildStore(
                                    builder,
                                    rhs_value->llvm_value(),
                                    dim->data_as.llvm_ptr_to_storage
                                );
                            }
                            break;
                        }
                        case ast::Kind::DiscardStmt: {
                            auto discard_stmt = dynamic_cast<ast::DiscardStmt*>(stmt);

                            // evaluating the discarded expression:
                            auto discarded_exp = discard_stmt->discarded_exp();
                            auto discarded_llvm_value = emit_ro_llvm_value_for(discarded_exp);

                            // discarding it by setting it to a variable named discard ...:
                            // NOTE:
                            // - discard does not mean this expression is safe to optimize out.
                            // - on the contrary, it means this expression's result MUST be evaluated and discarded.
                            // NOTE:
                            // - cannot name because may be void.
                            // std::string discard_var_name = "discard @ " + discard_stmt->loc().cpp_str();
                            // LLVMSetValueName(discarded_llvm_value->llvm_value(), discard_var_name.c_str());

                            break;
                        }
                        case ast::Kind::SetStmt: {
                            auto set_stmt = dynamic_cast<ast::SetStmt*>(stmt);

                            auto lhs_exp = set_stmt->lhs_exp();
                            auto rhs_exp = set_stmt->rhs_exp();

                            auto lhs_l_value = emit_rw_llvm_value_for(lhs_exp);
                            help_assign_exp_to_l_value(lhs_l_value, rhs_exp);

                            break;
                        }
                        default: {
                            assert(0 && "NotImplemented: emitting LLVM for unknown chain statement.");
                        }
                    }
                }

                // emitting the chain suffix:
                if (chain_exp->suffix()) {
                    return emit_ro_llvm_value_for(chain_exp->suffix());
                } else {
                    return new RValue(exp, nullptr);
                }
            }
            default: {
                assert(0 && "NotImplemented: emitting LLVM for unknown expression kind.");
                return nullptr;
            }
        }
    }

    LValue* EmitDefsVisitor::emit_rw_llvm_value_for(ast::Exp* exp) {
        // NOTE on set-stmt/enable_write: (from dependency dispatcher)
        // - set X = Y means that X is an lvalue/writable value.
        // - in DD, we check that X is either a tuple or an ID.
        //   - spec accepts either ID or tuple of IDs.

        // - this lets us assume X = Tuple | Id
        //   - anything else is a DependencyDispatcher error
        //   - DD doubles as a syntax checker here, poor separation of concerns => should alter grammar

        // - here, must check that...
        //   - if (enable_write), each ID has mutable DimKind
        //   - if (enable_write), each Tuple must actually export an array of pointers.

        // - note that the type system does not verify mutability (for some bizarre reason).
        //   - adding mutability rules would further complicate the type solver
        //   - it is possible to check this here.

        types::Type* exp_type = exp->x_type_of_var()->get_type_soln();

        switch (exp->kind()) {
            case ast::Kind::IdExp: {
                auto id_exp = dynamic_cast<ast::IdExp*>(exp);
                auto id_type = exp_type;

                if (id_type->type_kind() != types::Kind::Void) {
                    std::string id_name = "loaded:" + id_exp->name().cpp_str();
                    auto dim = id_exp->x_defn()->x_llvm_dim();

                    // not all dims are writable.
                    bool is_dim_writable = ([dim] () {
                        switch (dim->dim_kind) {
                            case DimKind::Arg_InOut:
                            case DimKind::Arg_Out:
                            case DimKind::Var: {
                                return true;
                            }
                            default: {
                                return false;
                            }
                        }
                    })();
                    if (!is_dim_writable) {
                        assert(0 && "NotImplemented: posting feedback on `set-stmt` to non-writable IdExp.");
                    }

                    return new IdLValue(id_exp, dim);
                } else {
                    // we need not look up the ID again, since the scoper checks that all used IDs are defined first,
                    // and no memory is 'dim'-ed for 'void' type IDs.
                    return new IdLValue(id_exp, nullptr);
                }
            }
            case ast::Kind::TupleExp: {
                auto tuple_exp = dynamic_cast<ast::TupleExp*>(exp);
                auto tuple_type = exp_type;

                assert(0 && "NotImplemented: emit LValue* for ast::TupleExp");

                break;
            }
            default: {
                assert(0 && "NotImplemented: `emit_rw_llvm_value_for(exp)`");
                return nullptr;
            }
        }
    }

    //
    // Helpers:
    //

    void EmitDefsVisitor::help_assign_exp_to_l_value(LValue* lhs, ast::Exp* rhs) {
        auto builder = static_cast<LLVMBuilderRef>(m_compiler->llvm_builder());

        switch (lhs->l_value_kind()) {
            case LValueKind::Id: {
                auto lhs_value = dynamic_cast<IdLValue*>(lhs);
                auto rhs_value = emit_ro_llvm_value_for(rhs);

                auto lhs_type = lhs->exp()->x_type_of_var()->get_type_soln();
                if (lhs_type->type_kind() == types::Kind::Void) {
                    // do nothing!
                } else {
                    // std::cout << "LHS: " << std::endl << '\t';
                    // LLVMDumpValue(lhs_value->llvm_storage_ptr());
                    // std::cout << std::endl;
                    // std::cout << "RHS:" << std::endl << '\t';
                    // LLVMDumpValue(rhs_value->llvm_value());
                    // std::cout << std::endl;

                    LLVMBuildStore(
                        builder,
                        rhs_value->llvm_value(),
                        lhs_value->llvm_storage_ptr()
                    );
                }

                break;
            }
            case LValueKind::Tuple: {
                // todo: expect rhs is of tuple type and destructure assignment.
                assert(0 && "NotImplemented: assigning to a tuple LValue");
                break;
            }
        }
    }

    //
    // Tying together:
    //

    LLVMModuleRef emit_llvm_for_script(Compiler* compiler, ast::Script* script) {
        auto module = new_llvm_module_for(script);

        EmitHeadersVisitor header_visitor{compiler, script, module};
        auto emit_header_ok = header_visitor.visit(script);

        EmitDefsVisitor defs_visitor{compiler, script, module};
        auto emit_defs_ok = defs_visitor.visit(script);

        char* out_msg = nullptr;
        bool validate_ok = !LLVMVerifyModule(
            module,
            LLVMReturnStatusAction,
            &out_msg
        );
        if (!validate_ok) {
            std::cout
                << "A fatal compiler error occurred in the LLVM emitter" << std::endl
                << "- Although input was valid, a bug prevented output from being generated." << std::endl
                << "- LLVM says: " << std::endl
                << "    " << out_msg << std::endl;
        }

        if (emit_header_ok && emit_defs_ok) {
            return module;
        } else {
            return nullptr;
        }
    }

}