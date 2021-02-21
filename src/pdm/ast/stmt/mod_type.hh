/*

#ifndef INCLUDED_PDM_AST_STMT_TYPE_HH
#define INCLUDED_PDM_AST_STMT_TYPE_HH

#include <variant>

#include "pdm/core/intern.hh"
#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/type_spec/type_spec.hh"
// #include "mod_content.hh"

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
        ModTypeStmt(
            source::Loc loc, intern::String lhs_name, std::vector<TPattern*>&& lhs_tpatterns, TypeSpec* typespec
        );

        ModTypeStmt(
            source::Loc loc, intern::String lhs_name, std::vector<TPattern*>&& lhs_tpatterns,
            intern::String ext_mod_name, utf8::String ext_type_name
        );
      
      public:
        [[nodiscard]] intern::String lhs_name() const;
        [[nodiscard]] std::vector<TPattern*> const& lhs_tpatterns() const;

      public:
        enum class RhsKind {
            TypeSpec,
            Extern
        };
        [[nodiscard]] RhsKind rhs_kind() const;
        [[nodiscard]] TypeSpec* opt_rhs_typespec() const;
        [[nodiscard]] intern::String opt_rhs_ext_mod_name() const;
        [[nodiscard]] utf8::String opt_rhs_ext_type_name() const;

      public:
        [[nodiscard]] types::Var* x_defn_var() const;
        void x_defn_var(types::Var* defn_var);
    };

    inline ModTypeStmt::ModTypeStmt(
        source::Loc loc, intern::String lhs_name, std::vector<TPattern*>&& lhs_tpatterns,
        intern::String ext_mod_name, utf8::String ext_type_name
    )
    :   ModContentStmt(loc, Kind::ModTypeStmt),
        m_lhs_name(lhs_name),
        m_lhs_tpatterns(std::move(lhs_tpatterns)),
        m_rhs(ExternRhs{ext_mod_name, std::move(ext_type_name)}),
        m_x_defn_var(nullptr)
    {}

    inline ModTypeStmt::ModTypeStmt(
        source::Loc loc, intern::String lhs_name, std::vector<TPattern*>&& lhs_tpatterns,
        TypeSpec* typespec
    )
    :   ModContentStmt(loc, Kind::ModTypeStmt),
        m_lhs_name(lhs_name),
        m_lhs_tpatterns(std::move(lhs_tpatterns)),
        m_rhs(TypeSpecRhs{typespec}),
        m_x_defn_var(nullptr)
    {}

    inline types::Var* ModTypeStmt::x_defn_var() const {
        return m_x_defn_var;
    }

    inline void ModTypeStmt::x_defn_var(types::Var* defn_var) {
        m_x_defn_var = defn_var;
    }

    inline utf8::String ModTypeStmt::opt_rhs_ext_type_name() const {
        if (std::holds_alternative<ExternRhs>(m_rhs)) {
            return std::get<ExternRhs>(m_rhs).ext_type_name;
        } else {
            return {};
        }
    }

    inline intern::String ModTypeStmt::opt_rhs_ext_mod_name() const {
        if (std::holds_alternative<ExternRhs>(m_rhs)) {
            return std::get<ExternRhs>(m_rhs).ext_mod_name;
        } else {
            return {};
        }
    }

    inline TypeSpec *ModTypeStmt::opt_rhs_typespec() const {
        if (std::holds_alternative<TypeSpecRhs>(m_rhs)) {
            return std::get<TypeSpecRhs>(m_rhs).typespec;
        } else {
            return nullptr;
        }
    }

    inline ModTypeStmt::RhsKind ModTypeStmt::rhs_kind() const {
        if (std::holds_alternative<TypeSpecRhs>(m_rhs)) {
            return RhsKind::TypeSpec;
        } else {
            return RhsKind::Extern;
        }
    }

    inline std::vector<TPattern*> const& ModTypeStmt::lhs_tpatterns() const {
        return m_lhs_tpatterns;
    }

    inline intern::String ModTypeStmt::lhs_name() const {
        return m_lhs_name;
    }

}

#endif  // INCLUDED_PDM_AST_STMT_TYPE_HH

*/