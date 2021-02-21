#ifndef INCLUDED__PDM__AST__MODULE__MOD_EXP_HH
#define INCLUDED__PDM__AST__MODULE__MOD_EXP_HH

#include <vector>

#include "pdm/ast/node.hh"
#include "pdm/source/loc.hh"
#include "pdm/core/intern.hh"

namespace pdm::ast {
    class TPattern;
    class Exp;
    class TypeSpec;
    class ClassSpec;
}

namespace pdm::ast {

    class ModExp: public Node {
      public:
        class Field: public Node {
          private:
            intern::String m_name;
          protected:
            Field(source::Loc field_loc, ast::Kind field_kind, intern::String field_name);
          public:
            [[nodiscard]] intern::String name() const;
        };
        class ValueField: public ModExp::Field {
          private:
            Exp* m_rhs_exp;
          protected:
            ValueField(source::Loc field_loc, intern::String name, Exp* rhs_exp_spec);
          public:
            [[nodiscard]] Exp* rhs_exp() const;
        };
        class TypeField: public ModExp::Field {
          private:
            TypeSpec* m_rhs_type_spec;
          protected:
            TypeField(source::Loc field_loc, intern::String name, TypeSpec* rhs_type_spec);
          public:
            [[nodiscard]] TypeSpec* rhs_type_spec() const;
        };
        class ClassField: public ModExp::Field {
          private:
            ClassSpec* m_rhs_class_spec;
          protected:
            ClassField(source::Loc field_loc, intern::String name, ClassSpec* rhs_class_spec);
          public:
            [[nodiscard]] ClassSpec* rhs_class_spec() const;
        };
        class ModuleField: public ModExp::Field {
            ModExp* m_rhs_mod_exp;
        };

      private:
        std::vector<ModExp::Field*> m_fields;
        ast::TPattern*              m_opt_template_pattern;

      public:
        ModExp(source::Loc loc, std::vector<ModExp::Field*>&& fields, ast::TPattern* opt_template_pattern)
        :   Node(loc, ast::Kind::ModExp),
            m_opt_template_pattern(opt_template_pattern)
        {}

      public:
        [[nodiscard]] std::vector<ModExp::Field*> const& fields() const;
        [[nodiscard]] ast::TPattern* opt_template_pattern() const;
    };

    //
    // Inline implementations:
    //

    inline ModExp::Field::Field(source::Loc field_loc, ast::Kind field_kind, intern::String field_name)
    :   Node(field_loc, field_kind),
        m_name(field_name)
    {}

    inline intern::String ModExp::Field::name() const {
        return m_name;
    }

    inline ModExp::ValueField::ValueField(source::Loc field_loc, intern::String name, Exp *rhs_exp_spec)
    :   ModExp::Field(field_loc, ast::Kind::ValueModField, name),
        m_rhs_exp(rhs_exp_spec)
    {}

    inline ModExp::TypeField::TypeField(source::Loc field_loc, intern::String name, TypeSpec *rhs_type_spec)
    :   ModExp::Field(field_loc, ast::Kind::TypeModField, name),
        m_rhs_type_spec(rhs_type_spec)
    {}

    inline ModExp::ClassField::ClassField(source::Loc field_loc, intern::String name, ClassSpec *rhs_class_spec)
    :   ModExp::Field(field_loc, ast::Kind::ClassModField, name),
        m_rhs_class_spec(rhs_class_spec)
    {}

    inline Exp* ModExp::ValueField::rhs_exp() const {
        return m_rhs_exp;
    }
    inline TypeSpec* ModExp::TypeField::rhs_type_spec() const {
        return m_rhs_type_spec;
    }
    inline ClassSpec* ModExp::ClassField::rhs_class_spec() const {
        return m_rhs_class_spec;
    }

    inline std::vector<ModExp::Field*> const& ModExp::fields() const {
        return m_fields;
    }
    inline ast::TPattern* ModExp::opt_template_pattern() const {
        return m_opt_template_pattern;
    }

}

#endif  // INCLUDED__PDM__AST__MODULE__MOD_EXP_HH