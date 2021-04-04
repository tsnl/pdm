#include "llvm-emitter.hh"

#include <iostream>

#include <filesystem>
#include <fstream>
#include <vector>
#include <stack>
#include <map>

#include "pdm/ast/stmt/vax.hh"
#include "pdm/types/type.hh"

#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>


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
                    // For 'out' and 'inout' parameters, pointers to the user type are passed
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
    //

    class EmitHeadersVisitor: public BaseScriptVisitor {
      public:
        EmitHeadersVisitor(
            Compiler* compiler,
            ast::ISourceNode* source_node,
            LLVMModuleRef output_module
        );

      public:
        [[nodiscard]] bool on_visit_lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) override;
        [[nodiscard]] bool on_visit_string_exp(ast::StringExp *node, VisitOrder visit_order) override;
    };

    EmitHeadersVisitor::EmitHeadersVisitor(
        Compiler* compiler,
        ast::ISourceNode* source_node,
        LLVMModuleRef output_module
    )
    :   BaseScriptVisitor(compiler, source_node, output_module)
    {}

    bool EmitHeadersVisitor::on_visit_lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) {
        if (visit_order == VisitOrder::Post) {
            std::string lambda_name = (
                "lambda @ " + node->loc().cpp_str()
            );
            auto fn_type = node->x_type_of_var()->get_type_soln();
            assert(fn_type && "Expected 'soln' type after typer for 'lambda-exp' in 'EmitHeaders'");
            LLVMTypeRef llvm_fn_type = emit_llvm_type_for(fn_type);
            LLVMValueRef llvm_fn = LLVMAddFunction(m_output_module, lambda_name.c_str(), llvm_fn_type);
            node->x_llvm_fn(llvm_fn);
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
    // Emitting module defs:
    //

    class EmitDefsVisitor: public BaseScriptVisitor {
      public:
        struct Frame {
            LLVMValueRef anonymous_fn;
            LLVMBasicBlockRef last_bb;
            std::map<intern::String, Dim*> symbols;
            ast::LambdaExp* defn_lambda_exp;
        };

      private:
        void fn_push(ast::LambdaExp* node, LLVMValueRef anonymous_llvm_header_fn);
        Dim* fn_dim(DimKind, intern::String name, types::Type* content_type);
        Dim* fn_lookup(intern::String name, bool read_enabled, bool write_enabled);
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

        bool emit_fn(ast::LambdaExp* lambda_node, LLVMValueRef llvm_fn);

      public:
        [[nodiscard]] bool on_visit_lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) override;

      public:
        [[nodiscard]] LLVMValueRef emit_llvm_value_for(ast::Exp* exp);
    };

    inline EmitDefsVisitor::EmitDefsVisitor(
        Compiler* compiler,
        ast::ISourceNode* source_node,
        LLVMModuleRef output_module
    )
    :   BaseScriptVisitor(compiler, source_node, output_module),
        m_compiler(compiler),
        m_fn_stack()
    {}

    void EmitDefsVisitor::fn_push(ast::LambdaExp* node, LLVMValueRef anonymous_llvm_header_fn) {
        auto frame = new Frame{};
        frame->anonymous_fn = anonymous_llvm_header_fn;
        frame->last_bb = nullptr;
        frame->defn_lambda_exp = node;

        // pushing to the stack:
        m_fn_stack.push_back(frame);
        fn_aux_on_top_frame_chg();
    }

    Dim* EmitDefsVisitor::fn_dim(DimKind dim_kind, intern::String name, types::Type* content_type) {
        assert(!m_fn_stack.empty() && "Cannot invoke `fn_dim` before `fn_push`");
        Frame* top_frame = m_fn_stack.back();

        LLVMTypeRef user_dim_type = emit_llvm_type_for(content_type);
        LLVMTypeRef true_dim_type = nullptr; {
            switch (dim_kind) {
                case DimKind::Arg_InOut:
                case DimKind::Arg_Out: {
                    // passing the pointer type
                    true_dim_type = LLVMPointerType(user_dim_type, 0);
                    break;
                }
                default: {
                    // passing the type as it is
                    true_dim_type = user_dim_type;
                    break;
                }
            }
        }

        std::string dim_kind_string = ([dim_kind] () {
            switch (dim_kind) {
                case DimKind::Arg_In: return "arg-in";
                case DimKind::Arg_Out: return "arg-out";
                case DimKind::Arg_InOut: return "arg-inout";
                case DimKind::Var: return "var";
                case DimKind::Val: return "val";
            }
        }());
        std::string dim_name = "dim[" + dim_kind_string + "]:" + name.cpp_str();

        assert(true_dim_type && "BUG: expected `actual_dim_content` != nullptr");
        LLVMValueRef stack_ptr = LLVMBuildAlloca(
            m_compiler->llvm_builder(),
            true_dim_type,
            dim_name.c_str()
        );

        auto dim = new Dim{}; {
            dim->dim_kind = dim_kind;
            dim->llvm_stack_ptr = stack_ptr;
            dim->llvm_user_dim_type = user_dim_type;
            dim->llvm_true_dim_type = true_dim_type;
        }

        // NOTE: symbols can overwrite each-other, in which case emitting garbage collection
        // for shadowed symbols should occur here:
        if (top_frame->symbols.contains(name)) {
            // todo: invoke destructor for shadowed, and now concealed symbol
        }
        top_frame->symbols[name] = dim;

        return dim;
    }

    Dim* EmitDefsVisitor::fn_lookup(intern::String name, bool read_enabled, bool write_enabled) {
        // NOTE:
        //   - looking up in a symbol table is not required, since all lookups have already
        //     been resolved in the scoper.
        //   - however, this approach easily enables defining symbols not defined by user code,
        //     so I'm sticking to the more flexible approach for now.

        // retrieving the 'dim':
        Dim* found_dim = nullptr; {
            for (
                int scan_index = static_cast<int>(m_fn_stack.size()) - 1;
                scan_index >= 0;
                scan_index--
            ) {
                Frame* scan_frame = m_fn_stack[scan_index];
                auto scan_it = scan_frame->symbols.find(name);
                if (scan_it != scan_frame->symbols.end()) {
                    // symbol found!
                    found_dim = scan_it->second;
                } else {
                    // symbol not found in this frame, keep scanning.
                    continue;
                }
            }
        }
        assert(found_dim && "Expected to catch undefined symbols in the 'scoper'.");
        return found_dim;
    }

    void EmitDefsVisitor::fn_pop() {
        assert(!m_fn_stack.empty() && "Cannot invoke `fn_pop` before `fn_push`");
        m_fn_stack.pop_back();

        fn_aux_on_top_frame_chg();
    }

    void EmitDefsVisitor::fn_aux_on_top_frame_chg() {
        if (!m_fn_stack.empty()) {
            Frame* top_frame = m_fn_stack.back();

            if (top_frame->last_bb == nullptr) {
                top_frame->last_bb = LLVMAppendBasicBlock(top_frame->anonymous_fn, "fn_entry_point");
            }

            LLVMPositionBuilderAtEnd(m_compiler->llvm_builder(), top_frame->last_bb);
        } else {
            LLVMClearInsertionPosition(m_compiler->llvm_builder());
        }
    }

    bool EmitDefsVisitor::emit_fn(ast::LambdaExp* lambda_node, LLVMValueRef llvm_fn) {
        // creating a basic block for an entry point:
        fn_push(lambda_node, llvm_fn);

        // alloca-ing space for each argument:
        // - arguments are always copied into on-stack space using 'dim'
        // - inout and out params copy a pointer to the actual arg rather than a value
        std::vector<ast::VPattern::Field*> const& fields = lambda_node->lhs_vpattern()->fields();
        for (size_t arg_index = 0; arg_index < fields.size(); arg_index++) {

            // 'dim'-ing (pushing) memory on the stack for this argument:
            ast::VPattern::Field* arg_field = fields[arg_index];
            DimKind dim_kind = ([arg_field] () {
                switch (arg_field->accepted_varg_kind()) {
                    case ast::VArgAccessSpec::In: return DimKind::Arg_In;
                    case ast::VArgAccessSpec::Out: return DimKind::Arg_Out;
                    case ast::VArgAccessSpec::InOut: return DimKind::Arg_InOut;
                }
            }());
            Dim* dim = fn_dim(dim_kind, arg_field->lhs_name(), arg_field->x_defn_tv()->get_type_soln());
            assert(dim && "Failed to 'dim' for fn-arg.");

            // storing the argument into this stack variable:
            LLVMValueRef init_store_value = LLVMGetParam(llvm_fn, arg_index);
            LLVMBuildStore(m_compiler->llvm_builder(), init_store_value, dim->llvm_stack_ptr);
        }


        // emitting the body, then a return instruction:
        // NOTE:
        //  even if we return void, must still emit the function body because
        //  there may be side-effects.
        // NOTE:
        //   'void' expressions return a 'nullptr' handle when emitting.

        // body:
        LLVMValueRef llvm_return_value = emit_llvm_value_for(lambda_node->rhs_body());

        // return instruction:
        types::Type* return_type = lambda_node->x_type_of_var()->get_type_soln();
        if (return_type->type_kind() == types::Kind::Void) {
            assert(
                llvm_return_value != nullptr &&
                "LlvmEmitter: expected nullptr llvm_return_value for void return"
            );
            LLVMBuildRetVoid(m_compiler->llvm_builder());
        } else {
            assert(
                llvm_return_value != nullptr &&
                "LlvmEmitter: expected non-nullptr llvm_return_value for non-void return"
            );
            LLVMBuildRet(m_compiler->llvm_builder(), llvm_return_value);
        }

        // popping the frame
        fn_pop();
        return true;
    }

    bool EmitDefsVisitor::on_visit_lambda_exp(ast::LambdaExp* node, ast::Visitor::VisitOrder visit_order) {
        auto lambda_ok = TinyVisitor::on_visit_lambda_exp(node, visit_order);
        if (!lambda_ok) {
            return false;
        }
        if (visit_order == VisitOrder::Pre) {
            auto lambda_node = dynamic_cast<ast::LambdaExp*>(node);
            LLVMValueRef llvm_fn = lambda_node->x_llvm_fn();

            if (!emit_fn(lambda_node, llvm_fn)) {
                return false;
            }
        }
        return true;
    }

    LLVMValueRef EmitDefsVisitor::emit_llvm_value_for(ast::Exp* exp) {
        types::Type* exp_type = exp->x_type_of_var()->get_type_soln();

        switch (exp->kind()) {
            case ast::Kind::UnitExp: {
                return LLVMGetUndef(LLVMVoidType());
            }
            case ast::Kind::IntExp: {
                auto int_exp = dynamic_cast<ast::IntExp*>(exp);
                auto int_type = dynamic_cast<types::IntType*>(exp_type);
                assert(int_exp && int_type && "Incorrect datatypes in int-exp.");
                return LLVMConstInt(
                    emit_llvm_type_for(exp_type),
                    int_exp->value(),
                    int_type->using_sign_ext()
                );
            }
            case ast::Kind::FloatExp: {
                auto float_exp = dynamic_cast<ast::FloatExp*>(exp);
                assert(float_exp && "Incorrect datatypes in float-exp.");
                return LLVMConstReal(
                    emit_llvm_type_for(exp_type),
                    static_cast<double>(float_exp->value())
                );
                break;
            }
            case ast::Kind::IdExp: {
                auto id_exp = dynamic_cast<ast::IdExp*>(exp);
                auto id_type = exp_type;
                if (id_type->type_kind() != types::Kind::Void) {
                    std::string id_name = "loaded:" + id_exp->name().cpp_str();
                    auto dim = fn_lookup(id_exp->name(), true, false);
                    return LLVMBuildLoad(
                        m_compiler->llvm_builder(),
                        dim->llvm_stack_ptr,
                        id_name.c_str()
                    );
                } else {
                    return LLVMGetUndef(LLVMVoidType());
                }
            }
//            case ast::Kind::StringExp: {
//                break;
//            }
//            case ast::Kind::UnaryExp: {
//                break;
//            }
//            case ast::Kind::BinaryExp: {
//                break;
//            }
//            case ast::Kind::LambdaExp: {
//                break;
//            }
//            case ast::Kind::IfExp: {
//                break;
//            }
//            case ast::Kind::VCallExp: {
//                break;
//            }
            case ast::Kind::ChainExp: {
                auto chain_exp = dynamic_cast<ast::ChainExp*>(exp);

                // emitting the chain prefix:
                for (auto stmt: chain_exp->prefix()) {
                    switch (stmt->kind()) {
                        case ast::Kind::VarStmt: {
                            auto vax_stmt = dynamic_cast<ast::VaxStmt*>(stmt);
                            assert(vax_stmt && "LlvmEmitter: Invalid 'var' stmt datatype in chain-exp.");

                            // evaluating the RHS exp:
                            auto rhs_value = emit_llvm_value_for(vax_stmt->rhs_exp());

                            // storing into LHS variables:
                            if (vax_stmt->lhs_lpattern()->destructure()) {
                                assert(0 && "NotImplemented: emitting LLVM IR for de-structured lpatterns.");
                            } else {
                                auto sole_field = vax_stmt->lhs_lpattern()->fields()[0];
                                assert(sole_field && "LlvmEmitter: nullptr field in lpattern");

                                auto sole_field_type = sole_field->x_defn_tv()->get_type_soln();
                                Dim* dim = fn_dim(
                                    DimKind::Var,
                                    sole_field->lhs_name(),
                                    sole_field_type
                                );
                                assert(dim && "LlvmEmitter: Failed to 'dim' for 'var' statement.");

                                LLVMBuildStore(
                                    m_compiler->llvm_builder(),
                                    rhs_value,
                                    dim->llvm_stack_ptr
                                );
                            }
                            break;
                        }
                        case ast::Kind::ValStmt: {
                            auto vax_stmt = dynamic_cast<ast::VaxStmt*>(stmt);
                            assert(vax_stmt && "Invalid 'vax' stmt datatype in chain-exp.");

                            // evaluating the RHS exp:
                            auto rhs_value = emit_llvm_value_for(vax_stmt->rhs_exp());

                            // storing into LHS variables:
                            if (vax_stmt->lhs_lpattern()->destructure()) {
                                assert(0 && "NotImplemented: emitting LLVM IR for de-structured lpatterns.");
                            } else {
                                auto sole_field = vax_stmt->lhs_lpattern()->fields()[0];
                                assert(sole_field && "LlvmEmitter: nullptr field in lpattern");

                                auto sole_field_type = sole_field->x_defn_tv()->get_type_soln();
                                Dim* dim = fn_dim(
                                    DimKind::Var,
                                    sole_field->lhs_name(),
                                    sole_field_type
                                );
                                assert(dim && "LlvmEmitter: Failed to 'dim' for 'var' statement.");

                                LLVMBuildStore(
                                    m_compiler->llvm_builder(),
                                    rhs_value,
                                    dim->llvm_stack_ptr
                                );
                            }
                            break;
                        }
                        case ast::Kind::DiscardStmt: {
                            auto discard_stmt = dynamic_cast<ast::DiscardStmt*>(stmt);

                            // evaluating the discarded expression:
                            auto discarded_exp = discard_stmt->discarded_exp();
                            LLVMValueRef discarded_llvm_value = emit_llvm_value_for(discarded_exp);

                            // discarding it by setting it to a variable named discard ...:
                            // NOTE:
                            // - discard does not mean this expression is safe to optimize out.
                            // - on the contrary, it means this expression's result MUST be evaluated and discarded.
                            std::string discard_var_name = "discard @ " + discard_stmt->loc().cpp_str();
                            LLVMSetValueName(discarded_llvm_value, discard_var_name.c_str());

                            break;
                        }
                        default: {
                            assert(0 && "NotImplemented: emitting LLVM for unknown chain statement.");
                        }
                    }
                }

                // emitting the chain suffix:
                return emit_llvm_value_for(chain_exp->suffix());
            }
            default: {
                assert(0 && "NotImplemented: emitting LLVM for unknown expression kind.");
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