#ifndef INCLUDED_PDM_AST_TYPESPEC_TUPLE_HH
#define INCLUDED_PDM_AST_TYPESPEC_TUPLE_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/setspec/type_spec.hh"

namespace pdm::ast {
    class Manager;
}

namespace pdm::ast {

    class TupleTypeSpec: public TypeSpec {
        friend Manager;

      private:
        std::vector<TypeSpec*> m_items;

      protected:
        TupleTypeSpec(source::Loc loc, std::vector<TypeSpec*>&& items);

      public:
        [[nodiscard]] std::vector<TypeSpec*> const& items() const;
    };

    inline std::vector<TypeSpec*> const& TupleTypeSpec::items() const {
        return m_items;
    }

    inline TupleTypeSpec::TupleTypeSpec(source::Loc loc, std::vector<TypeSpec*>&& items)
    :   TypeSpec(loc, Kind::TupleTypeSpec),
        m_items(std::move(items)) {}

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_TYPESPEC_TUPLE_HH
