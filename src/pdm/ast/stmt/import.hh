#ifndef INCLUDED_PDM_AST_STMT_IMPORT_HH
#define INCLUDED_PDM_AST_STMT_IMPORT_HH

#include "pdm/core/intern.hh"
#include "pdm/ast/stmt/stmt.hh"
#include "pdm/ast/exp/exp.hh"

namespace pdm::ast {

    class Manager;

    class ImportStmt: public Stmt {
      private:
        intern::String  m_imported_name;
        Exp*            m_imported_from_exp;
        Exp*            m_imported_type_exp;

      protected:
        ImportStmt(source::Loc loc, intern::String imported_name, Exp* imported_from_exp, Exp* imported_type_exp)
        : Stmt(loc, Kind::ImportStmt),
          m_imported_name(imported_name),
          m_imported_from_exp(imported_from_exp),
          m_imported_type_exp(imported_type_exp) {}
      
      public:
        intern::String imported_name() const {
            return m_imported_name;
        }
        Exp* imported_from_exp() const {
            return m_imported_from_exp;
        }
    };

}

#endif  // INCLUDED_PDM_AST_STMT_IMPORT_HH