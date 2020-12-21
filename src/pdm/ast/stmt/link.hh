#ifndef INCLUDED_PDM_AST_STMT_LINK_HH
#define INCLUDED_PDM_AST_STMT_LINK_HH

#include <vector>

#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/exp/string.hh"
#include "pdm/ast/exp/array.hh"

namespace pdm::ast {

    class Manager;

    class LinkStmt: public Stmt {
        friend Manager;

      public:
        enum class ItemKind {
            Val,
            Val_From,
            Type,
            Type_From
        };
        class Item {
          private:
            LinkStmt::ItemKind m_kind;
            intern::String     m_dst_name;
            Exp*               m_src_name;
          public:
            Item(LinkStmt::ItemKind kind, intern::String dst_name, Exp* src_name)
            : m_kind(kind),
              m_dst_name(dst_name),
              m_src_name(src_name) {}

          public:
            LinkStmt::ItemKind kind() const {
                return m_kind;
            }
            intern::String dst_name() const {
                return m_dst_name;
            }
            Exp* src_name() const {
                return m_src_name;
            }
        };

      private:
        Exp*                        m_linkage_name_exp;          // typer: req const, req == "C"
        Exp*                        m_linked_file_array_exp;     // typer: req const, string array
        std::vector<LinkStmt::Item> m_items;
      
      public:
        LinkStmt(source::Loc loc, Exp* linkage_name_exp, Exp* linked_file_array_exp, std::vector<LinkStmt::Item>&& items)
        : Stmt(loc, Kind::LinkStmt),
          m_linkage_name_exp(linkage_name_exp),
          m_linked_file_array_exp(linked_file_array_exp),
          m_items(std::move(items)) {}

      public:
        Exp* linkage_name_exp() const {
            return m_linkage_name_exp;
        }
        Exp* linked_file_array_exp() const {
            return m_linked_file_array_exp;
        }
        std::vector<LinkStmt::Item> const& items() const {
            return m_items;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_LINK_HH
