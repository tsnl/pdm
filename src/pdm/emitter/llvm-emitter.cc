#include "llvm-emitter.hh"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

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
                return LLVMPointerType(LLVMInt32Type(), POINTER_ADDRESS_SPACE);
            }
            case types::Kind::UnsignedInt:
            case types::Kind::SignedInt: {
                return LLVMIntType(
                    dynamic_cast<types::IntType*>(type)->width_in_bits()
                );
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
                size_t num_args = raw_param_types_vec.size();
                std::vector<LLVMTypeRef> param_types_vec{num_args};
                for (size_t i = 0; i < raw_param_types_vec.size(); i++) {
                    param_types_vec[i] = emit_llvm_type_for(raw_param_types_vec[i].type);
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

    class ScriptVisitor_EmitHeaders: public BaseScriptVisitor {
      public:
        ScriptVisitor_EmitHeaders(
            Compiler* compiler,
            ast::ISourceNode* source_node,
            LLVMModuleRef output_module
        );

      public:
        [[nodiscard]] bool on_visit_lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) override;
        [[nodiscard]] bool on_visit_string_exp(ast::StringExp *node, VisitOrder visit_order) override;
    };

    ScriptVisitor_EmitHeaders::ScriptVisitor_EmitHeaders(
        Compiler* compiler,
        ast::ISourceNode* source_node,
        LLVMModuleRef output_module
    )
    :   BaseScriptVisitor(compiler, source_node, output_module)
    {}

    bool ScriptVisitor_EmitHeaders::on_visit_lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) {
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

    bool ScriptVisitor_EmitHeaders::on_visit_string_exp(ast::StringExp* node, VisitOrder visit_order) {
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

    class ScriptVisitor_EmitDefs: public BaseScriptVisitor {
      public:
        ScriptVisitor_EmitDefs(
            Compiler* compiler,
            ast::ISourceNode* source_node,
            LLVMModuleRef output_module
        );

        bool emit_fn(ast::LambdaExp* lambda_node, LLVMValueRef llvm_fn);

      public:
        [[nodiscard]] bool on_visit_lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) override;
    };

    inline ScriptVisitor_EmitDefs::ScriptVisitor_EmitDefs(
        Compiler* compiler,
        ast::ISourceNode* source_node,
        LLVMModuleRef output_module
    )
    :   BaseScriptVisitor(compiler, source_node, output_module)
    {}

    bool ScriptVisitor_EmitDefs::emit_fn(ast::LambdaExp* lambda_node, LLVMValueRef llvm_fn) {
        LLVMBasicBlockRef entry_bb = LLVMAppendBasicBlock(llvm_fn, "entry-point");
        LLVMPositionBuilderAtEnd(m_compiler->llvm_builder(), entry_bb);

        // storing formal arguments in the entry BB:
        // - all params use pointers to existing arguments
        assert(0 && "NotImplemented: `emit_fn` WIP");

        return true;
    }

    bool ScriptVisitor_EmitDefs::on_visit_lambda_exp(ast::LambdaExp* node, ast::Visitor::VisitOrder visit_order) {
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

    //
    // Tying together:
    //

    LLVMModuleRef emit_llvm_for_script(Compiler* compiler, ast::Script* script) {
        auto module = new_llvm_module_for(script);

        ScriptVisitor_EmitHeaders header_visitor{compiler, script, module};
        auto emit_ok = header_visitor.visit(script);

        if (emit_ok) {
            return module;
        } else {
            return nullptr;
        }
    }

}