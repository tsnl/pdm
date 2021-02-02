#ifndef INCLUDED__PDM__STMT__MOD_CONTENT_HH
#define INCLUDED__PDM__STMT__MOD_CONTENT_HH

#include "stmt.hh"

namespace pdm::ast {
    class ModStmt;
}

namespace pdm::ast {
    class ModContentStmt: public Stmt {
      private:
        ModStmt* m_opt_parent_mod_stmt;

      protected:
        inline ModContentStmt(source::Loc loc, Kind stmt_kind);
        
      public:
        [[nodiscard]] inline ModStmt* opt_parent_mod_stmt() const;
        inline void opt_parent_mod_stmt(ModStmt* mod_stmt);
    };
    inline ModContentStmt::ModContentStmt(source::Loc loc, Kind stmt_kind)
    :   Stmt(loc, stmt_kind),
        m_opt_parent_mod_stmt(nullptr) 
    {}
    inline ModStmt* ModContentStmt::opt_parent_mod_stmt() const {
        return m_opt_parent_mod_stmt;
    }
    inline void ModContentStmt::opt_parent_mod_stmt(ModStmt* mod_stmt) {
        m_opt_parent_mod_stmt = mod_stmt;
    }
}

#endif  // INCLUDED__PDM__STMT__MOD_CONTENT_HH