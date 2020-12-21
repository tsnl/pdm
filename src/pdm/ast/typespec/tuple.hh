#ifndef INCLUDED_PDM_AST_TYPESPEC_TUPLE_HH
#define INCLUDED_PDM_AST_TYPESPEC_TUPLE_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {

    class TupleTypespec: public Typespec {
      private:
        std::vector<Typespec*> m_items;

      protected:
        TupleTypespec(source::Loc loc, std::vector<Typespec*>&& items)
        : Typespec(loc, Kind::TupleTypespec),
          m_items(std::move(items)) {}

      public:
        std::vector<Typespec*> const& items() const {
            return m_items;
        }
    };

}   // namespace pdm::ast

#endif  // INCLUDED_PDM_AST_TYPESPEC_TUPLE_HH
