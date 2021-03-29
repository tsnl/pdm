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
                std::vector<LLVMTypeRef> param_types_vec;
                auto return_type = nullptr;
                // todo: extract args and return values from FnType.
                assert(0 && "NotImplemented: emitting LLVM types for FnType");
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
        bool on_visit_lambda_exp(ast::LambdaExp* node, VisitOrder visit_order);
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
            // todo: export the function's type
            auto fn_type = node->x_type_of_var()->get_type_soln();
            assert(fn_type && "Expected 'soln' type after typer.");
            LLVMTypeRef llvm_fn_type = emit_llvm_type_for(fn_type);
            LLVMValueRef llvm_fn = LLVMAddFunction(m_output_module, "lambda", llvm_fn_type);
            node->x_llvm_fn(llvm_fn);
        }
        return true;
    }

    //
    // Emitting module defs:
    //

    class ScriptVisitor_EmitDefs: public BaseScriptVisitor {
        ScriptVisitor_EmitDefs(
            Compiler* compiler,
            ast::ISourceNode* source_node,
            LLVMModuleRef output_module
        );
    };

    inline ScriptVisitor_EmitDefs::ScriptVisitor_EmitDefs(
        Compiler* compiler,
        ast::ISourceNode* source_node,
        LLVMModuleRef output_module
    )
    :   BaseScriptVisitor(compiler, source_node, output_module)
    {}

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