#ifndef INCLUDED_PDM_SCOPER_SCOPER_HH
#define INCLUDED_PDM_SCOPER_SCOPER_HH

#include <stack>

#include "pdm/ast/visitor.hh"
#include "pdm/scoper/context.hh"
#include "pdm/scoper/frame.hh"
#include "pdm/scoper/root_frame.hh"
#include "pdm/typer/typer.hh"
#include "pdm/printer/printer.hh"


namespace pdm::scoper {

    class Scoper;
    class ScoperVisitor;

    class Scoper: public ast::TinyVisitor {
        friend ScoperVisitor;

      private:
        struct IdExpLookupOrder      { ast::IdExp* id_exp; Context* lookup_context; };
        struct IdTypespecLookupOrder { ast::IdTypespec* id_typespec; Context* lookup_context; };
        struct ImportLookupOrder     { ast::ImportStmt* import_stmt; Context* lookup_context; };
        struct UsingLookupOrder      { ast::UsingStmt* using_stmt; Context* lookup_context; };

      private:
        typer::Typer*      m_typer;
        Frame*             m_root_frame;
        std::vector<IdExpLookupOrder>      m_id_exp_orders;
        std::vector<IdTypespecLookupOrder> m_id_typespec_orders;
        std::vector<ImportLookupOrder>     m_import_orders;
        std::vector<UsingLookupOrder>      m_using_orders;

        bool m_finished;

      public:
        Scoper(typer::Typer* typer);

      public:
        Frame*        root_frame() const { return m_root_frame; }
        typer::Typer* typer()      const { return m_typer; }
        bool          finished()   const { return m_finished; }

      public:
        // `scope` creates data structures needed to lookup IDs
        bool scope(ast::Script* script);
        
        // `finish` should be called after all imported scripts are scoped.
        // it traverses the constructed data-structure to set ASTN properties
        // and apply finishing touches (e.g. using/import links).
        bool finish();

      public:
        void print_debug_info(printer::Printer& printer);
    };

    class ScoperVisitor: public ast::Visitor {
        friend Scoper;

      private:
        Scoper* m_scoper_ref;
        int m_overhead_chain_exp_count;
        std::stack<DefnKind> m_vpattern_defn_kind_stack;
        std::stack<DefnKind> m_lpattern_defn_kind_stack;
        std::stack<Frame*> m_frame_stack;

      protected:
        ScoperVisitor(Scoper* scoper_ref);

      private:
        Scoper* scoper() const {
            return m_scoper_ref;
        }

      private:
        bool in_chain_exp()   { return m_overhead_chain_exp_count > 0; }
        void inc_overhead_chain_exp_count() { ++m_overhead_chain_exp_count; }
        void dec_overhead_chain_exp_count() { --m_overhead_chain_exp_count; }

      private:
        Frame* top_frame() const { return m_frame_stack.top(); }
      
      private:
        void push_frame(FrameKind frame_kind);
        void pop_frame();

      private:
        void place_id_exp_lookup_order(ast::IdExp* id_exp);
        void place_id_typespec_lookup_order(ast::IdTypespec* id_typespec);
        void place_import_lookup_order(ast::ImportStmt* import_stmt);
        void place_using_lookup_order(ast::UsingStmt* using_stmt);

      protected:
        // scripts:
        virtual bool on_visit__script(ast::Script* script, VisitOrder visit_order) override;

        // statements:
        virtual bool on_visit__mod_stmt(ast::ModStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__typeclass_stmt(ast::TypeclassStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__type_stmt(ast::TypeStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__enum_stmt(ast::EnumStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__fn_stmt(ast::FnStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__const_stmt(ast::ConstStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__val_stmt(ast::ValStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__var_stmt(ast::VarStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__extern_stmt(ast::ExternStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__import_stmt(ast::ImportStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__set_stmt(ast::SetStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__discard_stmt(ast::DiscardStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__using_stmt(ast::UsingStmt* node, VisitOrder visit_order) override;

        // expressions:
        virtual bool on_visit__unit_exp(ast::UnitExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__int_exp(ast::IntExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__float_exp(ast::FloatExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__string_exp(ast::StringExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__id_exp(ast::IdExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__paren_exp(ast::ParenExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__tuple_exp(ast::TupleExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__array_exp(ast::ArrayExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__struct_exp(ast::StructExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__type_query_exp(ast::TypeQueryExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__chain_exp(ast::ChainExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__lambda_exp(ast::LambdaExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__if_exp(ast::IfExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__dot_index_exp(ast::DotIndexExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__dot_name_exp(ast::DotNameExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__unary_exp(ast::UnaryExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__binary_exp(ast::BinaryExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__vcall_exp(ast::VCallExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__tcall_exp(ast::TCallExp* node, VisitOrder visit_order) override;

        // patterns:
        virtual bool on_visit__vpattern(ast::VPattern* node, VisitOrder visit_order) override;
        virtual bool on_visit__tpattern(ast::TPattern* node, VisitOrder visit_order) override;
        virtual bool on_visit__lpattern(ast::LPattern* node, VisitOrder visit_order) override;

        // typespecs:
        virtual bool on_visit__id_typespec(ast::IdTypespec* node, VisitOrder visit_order) override;
        virtual bool on_visit__fn_typespec(ast::FnTypespec* node, VisitOrder visit_order) override;
        virtual bool on_visit__tcall_typespec(ast::TCallTypespec* node, VisitOrder visit_order) override;
        virtual bool on_visit__paren_typespec(ast::ParenTypespec* node, VisitOrder visit_order) override;
        virtual bool on_visit__tuple_typespec(ast::TupleTypespec* node, VisitOrder visit_order) override;
        virtual bool on_visit__dot_name_typespec_type_prefix(ast::DotNameTypespec_TypePrefix* node, VisitOrder visit_order) override;
        virtual bool on_visit__dot_name_typespec_mod_prefix(ast::DotNameTypespec_ModPrefix* node, VisitOrder visit_order) override;
        virtual bool on_visit__struct_typespec(ast::StructTypespec* node, VisitOrder visit_order) override;

        // args:
        virtual bool on_visit__targ(ast::TArg* targ, VisitOrder visit_order) override;
        virtual bool on_visit__varg(ast::VArg* varg, VisitOrder visit_order) override;

        // non-syntax:
        virtual bool on_visit__builtin_type_stmt(ast::BuiltinTypeStmt* node, VisitOrder visit_order) override;
    };

}

#endif  // INCLUDED_PDM_SCOPER_SCOPER_HH
