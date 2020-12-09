#ifndef INCLUDED_PDM_SCOPER_SCOPER_HH
#define INCLUDED_PDM_SCOPER_SCOPER_HH

#include <stack>

#include "pdm/ast/visitor.hh"
#include "pdm/scoper/context.hh"
#include "pdm/scoper/frame.hh"
#include "pdm/typer/typer.hh"

namespace pdm::scoper {

    class Scoper: public ast::Visitor {
      private:
        typer::Typer*      m_typer;
        std::stack<Frame*> m_frame_stack;

      public:
        Scoper(typer::Typer* typer, Frame* base_frame)
        : m_typer(typer),
          m_frame_stack() {
            m_frame_stack.push(base_frame);
        }

      protected:
        Frame* top_frame() {
            return m_frame_stack.top();
        }
        void push_frame(FrameKind frame_kind) {
            m_frame_stack.push(new Frame(frame_kind, top_frame()));
        }
        void pop_frame() {
            m_frame_stack.pop();
        }

      protected:

        // scripts:
        virtual bool on_visit__script(ast::Script* script, VisitOrder visit_order) override;

        // statements:
        virtual bool on_visit__module_stmt(ast::ModuleStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__typeclass_stmt(ast::TypeclassStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__type_stmt(ast::TypeStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__enum_stmt(ast::EnumStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__def_stmt(ast::DefStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__let_stmt(ast::LetStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__const_stmt(ast::ConstStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__link_stmt(ast::LinkStmt* node, VisitOrder visit_order) override;
        virtual bool on_visit__import_stmt(ast::ImportStmt* node, VisitOrder visit_order) override;

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
        virtual bool on_visit__v_call_exp(ast::VCallExp* node, VisitOrder visit_order) override;
        virtual bool on_visit__t_call_exp(ast::TCallExp* node, VisitOrder visit_order) override;
        
        // patterns:
        virtual bool on_visit__v_pattern(ast::VPattern* node, VisitOrder visit_order) override;
        virtual bool on_visit__t_pattern(ast::TPattern* node, VisitOrder visit_order) override;
        virtual bool on_visit__l_pattern(ast::LPattern* node, VisitOrder visit_order) override;

        // typespecs:
        virtual bool on_visit__id_typespec(ast::IdTypespec* node, VisitOrder visit_order) override;
        virtual bool on_visit__mut_typespec(ast::MutTypespec* node, VisitOrder visit_order) override;
        virtual bool on_visit__ptr_typespec(ast::PtrTypespec* node, VisitOrder visit_order) override;
        virtual bool on_visit__func_typespec(ast::FuncTypespec* node, VisitOrder visit_order) override;
        virtual bool on_visit__t_call_typespec(ast::TCallTypespec* node, VisitOrder visit_order) override;
        virtual bool on_visit__tuple_typespec(ast::TupleTypespec* node, VisitOrder visit_order) override;
        virtual bool on_visit__dot_name_typespec_type_prefix(ast::DotNameTypespec_TypePrefix* node, VisitOrder visit_order) override;
        virtual bool on_visit__dot_name_typespec_mod_prefix(ast::DotNameTypespec_ModPrefix* node, VisitOrder visit_order) override;
        virtual bool on_visit__struct_typespec(ast::StructTypespec* node, VisitOrder visit_order) override;
    };

}

#endif  // INCLUDED_PDM_SCOPER_SCOPER_HH