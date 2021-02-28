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
namespace pdm::types {
    class Var;
    class TypeVar;
}
namespace pdm::scoper {
    class Frame;
}

namespace pdm::ast {

    class ModExp: public Node {
      public:
        class Field: public Node {
          private:
            intern::String m_name;
            types::Var* m_x_defn_var;
          protected:
            Field(source::Loc field_loc, ast::Kind field_kind, intern::String field_name);
          public:
            [[nodiscard]] intern::String name() const;
          public:
            [[nodiscard]] types::Var* x_defn_var() const;
            void x_defn_var(types::Var* set_defn_var);
        };
        class ValueField: public ModExp::Field {
          private:
            Exp* m_rhs_exp;
          public:
            ValueField(source::Loc field_loc, intern::String field_name, Exp* rhs_exp);
          public:
            [[nodiscard]] Exp* rhs_exp() const;
        };
        class TypeField: public ModExp::Field {
          private:
            TypeSpec* m_rhs_type_spec;
          public:
            TypeField(source::Loc field_loc, intern::String field_name, TypeSpec* rhs_type_spec);
          public:
            [[nodiscard]] TypeSpec* rhs_type_spec() const;
        };
        class ClassField: public ModExp::Field {
          private:
            ClassSpec* m_rhs_class_spec;
          public:
            ClassField(source::Loc field_loc, intern::String field_name, ClassSpec* rhs_class_spec);
          public:
            [[nodiscard]] ClassSpec* rhs_class_spec() const;
        };
        class ModuleField: public ModExp::Field {
          private:
            ModExp* m_rhs_mod_exp;

          public:
            ModuleField(source::Loc field_loc, intern::String field_name, ModExp* rhs_mod_exp);

          public:
            [[nodiscard]] ModExp* rhs_mod_exp() const;
        };

      private:
        std::vector<ModExp::Field*> m_fields;
        ast::TPattern* m_opt_template_pattern;
        scoper::Frame* m_x_module_frame;
        types::TypeVar* m_x_module_var;

      public:
        ModExp(source::Loc loc, std::vector<ModExp::Field*>&& fields, ast::TPattern* opt_template_pattern);
        
      public:
        [[nodiscard]] std::vector<ModExp::Field*> const& fields() const;
        [[nodiscard]] ast::TPattern* opt_template_pattern() const;

      public:
        scoper::Frame* x_module_frame() const;
        void x_module_frame(scoper::Frame* new_frame);
        
        types::TypeVar* x_module_var() const;
        void x_module_var(types::TypeVar* module_tv);
    };

    //
    // Inline implementations:
    //

    inline ModExp::ModExp(source::Loc loc, std::vector<ModExp::Field*>&& fields, ast::TPattern* opt_template_pattern)
    :   Node(loc, ast::Kind::ModExp),
        m_fields(std::move(fields)),
        m_opt_template_pattern(opt_template_pattern),
        m_x_module_frame(nullptr),
        m_x_module_var(nullptr)
    {}

    inline ModExp::Field::Field(source::Loc field_loc, ast::Kind field_kind, intern::String field_name)
    :   Node(field_loc, field_kind),
        m_name(field_name)
    {}

    inline intern::String ModExp::Field::name() const {
        return m_name;
    }

    inline types::Var* ModExp::Field::x_defn_var() const {
        return m_x_defn_var;
    }
    
    inline void ModExp::Field::x_defn_var(types::Var* set_defn_var) {
        m_x_defn_var = set_defn_var;
    }

    inline ModExp::ValueField::ValueField(source::Loc field_loc, intern::String name, Exp *rhs_exp)
    :   ModExp::Field(field_loc, ast::Kind::ValueModField, name),
        m_rhs_exp(rhs_exp)
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

    inline scoper::Frame* ModExp::x_module_frame() const {
        return m_x_module_frame;
    }
    inline void ModExp::x_module_frame(scoper::Frame* new_frame) {
        m_x_module_frame = new_frame;
    }

    inline types::TypeVar* ModExp::x_module_var() const {
        return m_x_module_var;
    }
    inline void ModExp::x_module_var(types::TypeVar* module_tv) {
        m_x_module_var = module_tv;
    }

    inline ModExp::ModuleField::ModuleField(source::Loc field_loc, intern::String field_name, ModExp* rhs_mod_exp)
    :   ModExp::Field(field_loc, Kind::ModModField, field_name)
    {}

    inline ModExp* ModExp::ModuleField::rhs_mod_exp() const {
        return m_rhs_mod_exp;
    }
}

#endif  // INCLUDED__PDM__AST__MODULE__MOD_EXP_HH