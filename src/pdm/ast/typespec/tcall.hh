#ifndef INCLUDED_PDM_AST_TYPESPEC_TCALL_HH
#define INCLUDED_PDM_AST_TYPESPEC_TCALL_HH

#include "pdm/source/loc.hh"
#include "pdm/ast/kind.hh"
#include "pdm/ast/typespec/typespec.hh"

namespace pdm::ast {

    class TCallTypespec: public Typespec {
      public:
        class Arg {
          private:
            Node* m_node;
            bool  m_is_type_not_val;

          public:
            Arg(Node* node, bool is_type_not_val)
            : m_node(node), m_is_type_not_val(is_type_not_val) {}
            
            virtual ~Arg() {};
          
          public:
            Node* node() const { return m_node; }
            bool is_type_not_val() const { return m_is_type_not_val; }
        };

      private:
        Typespec*                       m_lhs_called;
        std::vector<TCallTypespec::Arg> m_args;
      public:
        TCallTypespec(source::Loc loc, Typespec* lhs_called, std::vector<TCallTypespec::Arg>&& args)
        : Typespec(loc, Kind::TCallTypespec),
          m_lhs_called(lhs_called),
          m_args(std::move(args)) {}
      
      public:
        Typespec* lhs_called() const {
            return m_lhs_called;
        }
        std::vector<TCallTypespec::Arg> const& args() const {
            return m_args;
        }
    };

}

#endif  // INCLUDED_PDM_AST_TYPESPEC_TCALL_HH