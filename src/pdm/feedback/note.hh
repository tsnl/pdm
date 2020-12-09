#ifndef INCLUDED_PDM_FEEDBACK_NOTE_HH
#define INCLUDED_PDM_FEEDBACK_NOTE_HH

#include <string>
#include <ostream>

#include "pdm/source/loc.hh"

namespace pdm::ast {
    class Node;
}

namespace pdm::feedback {

    class Note {
      private:
        std::string m_desc;

      public:
        Note(std::string&& desc)
        : m_desc(std::move(desc)) {}

      public:
        std::string const& desc() const {
            return m_desc;
        }
        virtual source::Loc const* opt_loc() const;

      public:
        void print(std::ostream& out, std::string const& indent_spacer = "    ") const;
    };

    class SourceLocNote: public Note {
      private:
        source::Loc m_loc;

      public:
        SourceLocNote(std::string&& desc, source::Loc loc)
        : Note(std::move(desc)),
          m_loc(loc) {}

      public:
        virtual source::Loc const* opt_loc() const override;
    };

    class AstNodeNote: public Note {
      private:
        ast::Node* m_node;

      public:
        AstNodeNote(std::string&& desc, ast::Node* ast_node)
        : Note(std::move(desc)),
          m_node(ast_node) {}

      public:
        virtual source::Loc const* opt_loc() const override;
    };

}

#endif  // INCLUDED_PDM_FEEDBACK_NOTE_HH