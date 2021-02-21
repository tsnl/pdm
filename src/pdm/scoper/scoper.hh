#ifndef INCLUDED_PDM_SCOPER_SCOPER_HH
#define INCLUDED_PDM_SCOPER_SCOPER_HH

#include <stack>

#include "pdm/ast/visitor.hh"
#include "pdm/scoper/context.hh"
#include "pdm/scoper/frame.hh"
#include "pdm/scoper/root_frame.hh"
#include "pdm/types/manager.hh"
#include "pdm/printer/printer.hh"


namespace pdm {
    class Compiler;
}
namespace pdm::scoper {
    class Scoper;
    class ScoperVisitor;
}

namespace pdm::scoper {

    class Scoper: public ast::TinyVisitor {
        friend ScoperVisitor;

      private:
        struct IdExpLookupOrder      { ast::IdExp* id_exp; Context* lookup_context; };
        struct IdTypeSpecLookupOrder { ast::IdTypeSpec* id_typespec; Context* lookup_context; };
        struct ImportLookupOrder     { ast::ImportStmt* import_stmt; Context* lookup_context; };
        struct UsingLookupOrder      { ast::UsingStmt* using_stmt; Context* lookup_context; };

      private:
        Compiler*                m_compiler_ptr;
        Frame*                             m_root_frame;
        std::vector<IdExpLookupOrder>      m_id_exp_orders;
        std::vector<IdTypeSpecLookupOrder> m_id_typespec_orders;
        std::vector<ImportLookupOrder>     m_import_orders;
        std::vector<UsingLookupOrder>      m_using_orders;

        bool m_finished;

      public:
        Scoper(Compiler* compiler_ptr);

      public:
        Frame*              root_frame() const { return m_root_frame; }
        Compiler* compiler()   const { return m_compiler_ptr; }
        bool                finished()   const { return m_finished; }

        types::Manager* types_mgr() const;

      public:
        // `scope` creates data structures needed to lookup IDs
        bool scope(ast::Script* script);
        
        // `finish` should be called after all imported scripts are scoped.
        // it traverses the constructed data-structure to set ASTN properties
        // and apply finishing touches (e.g. using/import links).
        bool finish();

      public:
        void print(printer::Printer& printer);
    };

    class ScoperVisitor: public ast::Visitor {
        friend Scoper;

      private:
        Scoper*              m_scoper_ref;
        int                  m_overhead_chain_exp_count;
        std::stack<DefnKind> m_vpattern_defn_kind_stack;
        std::stack<DefnKind> m_lpattern_defn_kind_stack;
        std::stack<Frame*>   m_frame_stack;

      protected:
        ScoperVisitor(Scoper* scoper_ref);

      private:
        [[nodiscard]] Scoper* scoper() const {
            return m_scoper_ref;
        }

      private:
        bool in_chain_exp()   { return m_overhead_chain_exp_count > 0; }
        void inc_overhead_chain_exp_count() { ++m_overhead_chain_exp_count; }
        void dec_overhead_chain_exp_count() { --m_overhead_chain_exp_count; }

      private:
        [[nodiscard]] Frame* top_frame() const { return m_frame_stack.top(); }
      
      private:
        void push_frame(FrameKind frame_kind);
        void pop_frame();

      private:
        void place_id_exp_lookup_order(ast::IdExp* id_exp);
        void place_id_type_spec_lookup_order(ast::IdTypeSpec* id_typespec);
        void place_import_lookup_order(ast::ImportStmt* import_stmt);
        void place_using_lookup_order(ast::UsingStmt* using_stmt);

      private:
        void post_overlapping_defn_error(std::string defn_kind, Defn const& failed_defn);
        void post_overlapping_defn_error(std::string defn_kind, Defn const& failed_defn, Context* tried_context) const;
        void help_post_defn_failure(std::string defn_kind, Defn const& failed_new_defn, Defn const& old_defn) const;

      protected:
        // scripts:
        bool on_visit_script(ast::Script* script, VisitOrder visit_order) override;

        // statements:
        bool on_visit_const_stmt(ast::ConstStmt* node, VisitOrder visit_order) override;
        bool on_visit_val_stmt(ast::ValStmt* node, VisitOrder visit_order) override;
        bool on_visit_var_stmt(ast::VarStmt* node, VisitOrder visit_order) override;
        bool on_visit_extern_stmt(ast::ExternStmt* node, VisitOrder visit_order) override;
        bool on_visit_import_stmt(ast::ImportStmt* node, VisitOrder visit_order) override;
        bool on_visit_set_stmt(ast::SetStmt* node, VisitOrder visit_order) override;
        bool on_visit_discard_stmt(ast::DiscardStmt* node, VisitOrder visit_order) override;
        bool on_visit_using_stmt(ast::UsingStmt* node, VisitOrder visit_order) override;

        // expressions:
        bool on_visit_unit_exp(ast::UnitExp* node, VisitOrder visit_order) override;
        bool on_visit_int_exp(ast::IntExp* node, VisitOrder visit_order) override;
        bool on_visit_float_exp(ast::FloatExp* node, VisitOrder visit_order) override;
        bool on_visit_string_exp(ast::StringExp* node, VisitOrder visit_order) override;
        bool on_visit_id_exp(ast::IdExp* node, VisitOrder visit_order) override;
        bool on_visit_paren_exp(ast::ParenExp* node, VisitOrder visit_order) override;
        bool on_visit_tuple_exp(ast::TupleExp* node, VisitOrder visit_order) override;
        bool on_visit_array_exp(ast::ArrayExp* node, VisitOrder visit_order) override;
        bool on_visit_struct_exp(ast::StructExp* node, VisitOrder visit_order) override;
        bool on_visit_type_query_exp(ast::TypeQueryExp* node, VisitOrder visit_order) override;
        bool on_visit_chain_exp(ast::ChainExp* node, VisitOrder visit_order) override;
        bool on_visit_lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) override;
        bool on_visit_if_exp(ast::IfExp* node, VisitOrder visit_order) override;
        bool on_visit_dot_index_exp(ast::DotIndexExp* node, VisitOrder visit_order) override;
        bool on_visit_dot_name_exp(ast::DotNameExp* node, VisitOrder visit_order) override;
        bool on_visit_module_dot_exp(ast::ModuleDotExp* node, VisitOrder visit_order) override;
        bool on_visit_unary_exp(ast::UnaryExp* node, VisitOrder visit_order) override;
        bool on_visit_binary_exp(ast::BinaryExp* node, VisitOrder visit_order) override;
        bool on_visit_v_call_exp(ast::VCallExp* node, VisitOrder visit_order) override;
        bool on_visit_t_call_exp(ast::TCallExp* node, VisitOrder visit_order) override;

        // patterns:
        bool on_visit_v_pattern(ast::VPattern* node, VisitOrder visit_order) override;
        bool on_visit_t_pattern(ast::TPattern* node, VisitOrder visit_order) override;
        bool on_visit_l_pattern(ast::LPattern* node, VisitOrder visit_order) override;

        // typespecs:
        bool on_visit_id_type_spec(ast::IdTypeSpec* node, VisitOrder visit_order) override;
        bool on_visit_id_class_spec(ast::IdClassSpec* node, VisitOrder visit_order) override;
        bool on_visit_fn_type_spec(ast::FnTypeSpec* node, VisitOrder visit_order) override;
        bool on_visit_tuple_type_spec(ast::TupleTypeSpec* node, VisitOrder visit_order) override;
        bool on_visit_struct_type_spec(ast::StructTypeSpec* node, VisitOrder visit_order) override;

        // args:
        bool on_visit_t_arg(ast::TArg* t_arg, VisitOrder visit_order) override;
        bool on_visit_v_arg(ast::VArg* v_arg, VisitOrder visit_order) override;

        // non-syntax:
        bool on_visit_builtin_type_stmt(ast::BuiltinStmt* node, VisitOrder visit_order) override;
    };

}

#endif  // INCLUDED_PDM_SCOPER_SCOPER_HH
