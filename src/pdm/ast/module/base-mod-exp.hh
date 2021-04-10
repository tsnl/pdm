#ifndef INCLUDED__PDM__AST__MODULE__BASE_MOD_HH
#define INCLUDED__PDM__AST__MODULE__BASE_MOD_HH

#include <vector>

#include "pdm/ast/node.hh"
#include "pdm/core/intern.hh"

namespace pdm::ast {
    class Exp;
    class TypeSpec;
    class ClassSpec;
}
namespace pdm::scoper {
    class Defn;
}
namespace pdm::types {
    class Var;
    class TypeVar;
}

namespace pdm::ast {

    // A ModExp is a **value** representing the contents of a module.
    class BaseModExp: public Node {
      public:
        class Field: public Node {
          private:
            intern::String m_name;
            scoper::Defn* m_x_defn;

          protected:
            Field(source::Loc field_loc, ast::Kind field_kind, intern::String field_name);

          public:
            [[nodiscard]] intern::String name() const;

          public:
            [[nodiscard]] scoper::Defn* x_defn() const;
            void x_defn(scoper::Defn* new_defn);

          public:
            [[nodiscard]] types::Var* x_defn_var() const;
        };

      public:
        class ValueField: public BaseModExp::Field {
          private:
            Exp* m_rhs_exp;
          public:
            ValueField(source::Loc field_loc, intern::String field_name, Exp* rhs_exp);
          public:
            [[nodiscard]] Exp* rhs_exp() const;
        };

      public:
        class TypeField: public BaseModExp::Field {
          private:
            TypeSpec* m_rhs_type_spec;
          public:
            TypeField(source::Loc field_loc, intern::String field_name, TypeSpec* rhs_type_spec);
          public:
            [[nodiscard]] TypeSpec* rhs_type_spec() const;
        };

      public:
        class ClassField: public BaseModExp::Field {
          private:
            ClassSpec* m_rhs_class_spec;
          public:
            ClassField(source::Loc field_loc, intern::String field_name, ClassSpec* rhs_class_spec);
          public:
            [[nodiscard]] ClassSpec* rhs_class_spec() const;
        };

      public:
        class ModuleField: public BaseModExp::Field {
          private:
            BaseModExp* m_rhs_mod_exp;

          public:
            ModuleField(source::Loc field_loc, intern::String field_name, BaseModExp* rhs_mod_exp);

          public:
            [[nodiscard]] BaseModExp* rhs_mod_exp() const;
        };

      protected:
        BaseModExp(source::Loc loc, ast::Kind kind, std::vector<Field*>&& fields);

      private:
        std::vector<Field*> m_fields;
        scoper::Frame* m_x_module_frame;
        types::TypeVar* m_x_module_var;

      public:
        [[nodiscard]] scoper::Frame* x_module_frame() const;
        void x_module_frame(scoper::Frame* frame);

        [[nodiscard]] types::TypeVar* x_module_var() const;
        void x_module_var(types::TypeVar* var);

      public:
        [[nodiscard]] std::vector<Field*> const& fields() const;
    };

    inline BaseModExp::BaseModExp(source::Loc loc, ast::Kind kind, std::vector<Field*>&& fields)
    :   Node{loc, kind},
        m_fields(std::move(fields)),
        m_x_module_frame{nullptr},
        m_x_module_var{nullptr}
    {}

    inline scoper::Frame* BaseModExp::x_module_frame() const {
        return m_x_module_frame;
    }
    inline void BaseModExp::x_module_frame(scoper::Frame* frame) {
        m_x_module_frame = frame;
    }

    inline types::TypeVar* BaseModExp::x_module_var() const {
        return m_x_module_var;
    }
    inline void BaseModExp::x_module_var(types::TypeVar *var) {
        m_x_module_var = var;
    }

    inline BaseModExp::Field::Field(source::Loc field_loc, ast::Kind field_kind, intern::String field_name)
    :   Node{field_loc, field_kind},
        m_name{field_name},
        m_x_defn{nullptr}
    {}

    inline intern::String BaseModExp::Field::name() const {
        return m_name;
    }

    inline BaseModExp::ValueField::ValueField(source::Loc field_loc, intern::String name, Exp *rhs_exp)
    :   BaseModExp::Field(field_loc, ast::Kind::NativeModExp_ValueField, name),
        m_rhs_exp(rhs_exp)
    {}

    inline BaseModExp::TypeField::TypeField(source::Loc field_loc, intern::String name, TypeSpec *rhs_type_spec)
    :   BaseModExp::Field(field_loc, ast::Kind::NativeModExp_TypeField, name),
        m_rhs_type_spec(rhs_type_spec)
    {}

    inline BaseModExp::ClassField::ClassField(source::Loc field_loc, intern::String name, ClassSpec *rhs_class_spec)
    :   BaseModExp::Field(field_loc, ast::Kind::NativeModExp_ClassField, name),
        m_rhs_class_spec(rhs_class_spec)
    {}

    inline BaseModExp::ModuleField::ModuleField(source::Loc field_loc, intern::String field_name, BaseModExp* rhs_mod_exp)
    :   BaseModExp::Field(field_loc, Kind::NativeModExp_ModField, field_name),
        m_rhs_mod_exp(rhs_mod_exp)
    {}

    inline Exp* BaseModExp::ValueField::rhs_exp() const {
        return m_rhs_exp;
    }
    inline TypeSpec* BaseModExp::TypeField::rhs_type_spec() const {
        return m_rhs_type_spec;
    }
    inline ClassSpec* BaseModExp::ClassField::rhs_class_spec() const {
        return m_rhs_class_spec;
    }

    inline std::vector<BaseModExp::Field*> const& BaseModExp::fields() const {
        return m_fields;
    }

    inline scoper::Defn* BaseModExp::Field::x_defn() const {
        return m_x_defn;
    }

    inline void BaseModExp::Field::x_defn(scoper::Defn* new_defn) {
        m_x_defn = new_defn;
    }

}

#endif  // INCLUDED__PDM__AST__MODULE__BASE_MOD_HH
