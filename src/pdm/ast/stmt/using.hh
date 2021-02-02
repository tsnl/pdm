#ifndef INCLUDED_PDM_AST_STMT_USING_HH
#define INCLUDED_PDM_AST_STMT_USING_HH

#include "stmt.hh"

namespace pdm::ast {
    class Manager;
    class Exp;
}

namespace pdm::ast {

    class UsingStmt: public Stmt {
        friend Manager;

      private:
        intern::String m_module_name;
        std::string    m_suffix;
    
      protected:
        UsingStmt(source::Loc loc, intern::String module_name, std::string suffix);

      public:
        [[nodiscard]] intern::String const& module_name() const;
        [[nodiscard]] std::string const& suffix() const;
    };

    inline UsingStmt::UsingStmt(source::Loc loc, intern::String module_name, std::string suffix)
    :   Stmt(loc, Kind::UsingStmt),
        m_module_name(module_name),
        m_suffix(std::move(suffix)) {}

    inline intern::String const& UsingStmt::module_name() const {
        return m_module_name;
    }

    inline std::string const& UsingStmt::suffix() const {
        return m_suffix;
    }

}

#endif  // INCLUDED_PDM_AST_STMT_USING_HH
