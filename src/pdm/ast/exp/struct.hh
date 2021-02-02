#ifndef INCLUDED_PDM_AST_EXP_STRUCT_HH
#define INCLUDED_PDM_AST_EXP_STRUCT_HH

#include <vector>

#include "pdm/ast/kind.hh"
#include "pdm/ast/exp/exp.hh"
#include "pdm/source/loc.hh"
#include "pdm/core/intern.hh"

namespace pdm::ast {

    class Manager;

    class StructExp: public Exp {
        friend Manager;

      public:
        class Field {
            friend Manager;

          private:
            source::Loc    m_loc;
            intern::String m_name;
            Exp*           m_value;

          protected:
            Field(source::Loc loc, intern::String name, Exp* value);
          
          public:
            [[nodiscard]] source::Loc const& loc() const;
            [[nodiscard]] intern::String name() const;
            [[nodiscard]] Exp* value() const;
        };

      private:
        std::vector<StructExp::Field*> m_fields;
    
      protected:
        StructExp(source::Loc loc, std::vector<StructExp::Field*>&& fields);

      public:
        [[nodiscard]] std::vector<StructExp::Field*> const& fields() const;
    };

    inline StructExp::Field::Field(source::Loc loc, intern::String name, Exp *value)
    :   m_loc(loc),
        m_name(name),
        m_value(value) {}

    inline source::Loc const& StructExp::Field::loc() const {
        return m_loc;
    }

    inline intern::String StructExp::Field::name() const {
        return m_name;
    }

    inline Exp* StructExp::Field::value() const {
        return m_value;
    }

    inline StructExp::StructExp(source::Loc loc, std::vector<StructExp::Field*>&& fields)
    :   Exp(loc, Kind::StructExp),
        m_fields(std::move(fields)) {}

    inline std::vector<StructExp::Field*> const& StructExp::fields() const {
        return m_fields;
    }

}

#endif  // INCLUDED_PDM_AST_EXP_STRUCT_HH