#ifndef INCLUDED_PDM_AST_STMT_TYPE_HH
#define INCLUDED_PDM_AST_STMT_TYPE_HH

#include <variant>

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/setspec/typespec.hh"
#include "mod_content.hh"

namespace pdm::ast {
    class Manager;
    class TPattern;
}
namespace pdm::types {
    class Var;
}

namespace pdm::ast {

    class ModTypeStmt: public ModContentStmt {
        friend Manager;

      private:
        struct TypeSpecRhs {
            TypeSpec* typespec;
        };
        struct ExternRhs {
            intern::String ext_mod_name;
            utf8::String ext_type_name;
        };

      private:
        intern::String                       m_lhs_name;
        std::vector<TPattern*>               m_lhs_tpatterns;
        std::variant<TypeSpecRhs, ExternRhs> m_rhs;
        types::Var*                          m_x_defn_var;

      public:
        ModTypeStmt(source::Loc loc, intern::String lhs_name, std::vector<TPattern*>&& lhs_tpatterns, TypeSpec* typespec)
        :   ModContentStmt(loc, Kind::ModTypeStmt),
            m_lhs_name(lhs_name),
            m_lhs_tpatterns(std::move(lhs_tpatterns)),
            m_rhs(TypeSpecRhs{typespec}),
            m_x_defn_var(nullptr)
        {}

        ModTypeStmt(source::Loc loc, intern::String lhs_name, std::vector<TPattern*>&& lhs_tpatterns, intern::String ext_mod_name, utf8::String ext_type_name)
        :   ModContentStmt(loc, Kind::ModTypeStmt),
            m_lhs_name(lhs_name),
            m_lhs_tpatterns(std::move(lhs_tpatterns)),
            m_rhs(ExternRhs{ext_mod_name, ext_type_name})
        {}
      
      public:
        intern::String lhs_name() const {
            return m_lhs_name;
        }
        std::vector<TPattern*> const& lhs_tpatterns() const {
            return m_lhs_tpatterns;
        }

      public:
        enum class RhsKind {
            TypeSpec,
            Extern
        };
        RhsKind rhs_kind() const {
            if (std::holds_alternative<TypeSpecRhs>(m_rhs)) {
                return RhsKind::TypeSpec;
            } else {
                return RhsKind::Extern;
            }
        }
        TypeSpec* opt_rhs_typespec() const {
            if (std::holds_alternative<TypeSpecRhs>(m_rhs)) {
                return std::get<TypeSpecRhs>(m_rhs).typespec;
            } else {
                return nullptr;
            }
        }
        intern::String opt_rhs_ext_mod_name() const {
            if (std::holds_alternative<ExternRhs>(m_rhs)) {
                return std::get<ExternRhs>(m_rhs).ext_mod_name;
            } else {
                return {};
            }
        }
        utf8::String opt_rhs_ext_type_name() const {
            if (std::holds_alternative<ExternRhs>(m_rhs)) {
                return std::get<ExternRhs>(m_rhs).ext_type_name;
            } else {
                return {};
            }
        }

      public:
        types::Var* x_defn_var() const {
            return m_x_defn_var;
        }
        void x_defn_var(types::Var* defn_var) {
            m_x_defn_var = defn_var;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_TYPE_HH