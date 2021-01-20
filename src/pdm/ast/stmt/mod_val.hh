#ifndef INCLUDED_PDM_AST_STMT_FN_HH
#define INCLUDED_PDM_AST_STMT_FN_HH

#include <variant>

#include "stmt.hh"
#include "pdm/ast/kind.hh"
#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "mod_content.hh"

namespace pdm::ast {   
    class Manager;
    class Exp;
    class TypeSpec;
    class VPattern;
    class TPattern;
}
namespace pdm::types {
    class Var;
}

namespace pdm::ast {

    class ModValStmt: public ModContentStmt {
        friend Manager;

      public:
        enum class RhsKind {
            Internal,
            External
        };
      private:
        struct ExpRhs {
            Exp* exp;
        };
        struct ExternRhs {
            intern::String ext_mod_name;
            utf8::String   ext_fn_name;
            TypeSpec*      ext_typespec;
        };

      private:
        intern::String                  m_name;
        std::vector<TPattern*>          m_tpatterns;
        std::variant<ExpRhs, ExternRhs> m_rhs;
        types::Var*                     m_x_defn_var;

      protected:
        ModValStmt(
            source::Loc loc,
            intern::String name,
            std::vector<TPattern*> tpatterns,
            Exp* rhs
        )
        :   ModContentStmt(loc, Kind::ModValStmt),
            m_name(name),
            m_tpatterns(std::move(tpatterns)),
            m_rhs(ExpRhs{rhs}),
            m_x_defn_var(nullptr)
        {}

        ModValStmt(
            source::Loc loc,
            intern::String name,
            std::vector<TPattern*> tpatterns,
            TypeSpec* ext_typespec,
            intern::String ext_mod_name,
            utf8::String ext_fn_name
        )
        :   ModContentStmt(loc, Kind::ModValStmt),
            m_name(name),
            m_tpatterns(std::move(tpatterns)),
            m_rhs(ExternRhs{ext_mod_name, ext_fn_name, ext_typespec}),
            m_x_defn_var(nullptr)
        {}

      public:
        intern::String name() const {
            return m_name;
        }
        std::vector<TPattern*> const& tpatterns() const {
            return m_tpatterns;
        }
      public:
        RhsKind rhs_kind() const {
            if (std::holds_alternative<ExpRhs>(m_rhs)) {
                return RhsKind::Internal;
            } else {
                return RhsKind::External;
            }
        }
        Exp* opt_rhs_exp() const {
            if (std::holds_alternative<ExpRhs>(m_rhs)) {
                return std::get<ExpRhs>(m_rhs).exp;
            } else {
                return nullptr;
            }
        }
        intern::String opt_rhs_ext_mod_name() const {
            if (std::holds_alternative<ExpRhs>(m_rhs)) {
                return std::get<ExternRhs>(m_rhs).ext_mod_name;
            } else {
                return {};
            }
        }
        utf8::String opt_rhs_ext_fn_name() const {
            if (std::holds_alternative<ExpRhs>(m_rhs)) {
                return std::get<ExternRhs>(m_rhs).ext_fn_name;
            } else {
                return {};
            }
        }

      // extension properties set by scoper:
      public:
        types::Var* x_defn_var() const {
            return m_x_defn_var;
        }
        void x_defn_var(types::Var* var) {
            m_x_defn_var = var;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_FN_HH
