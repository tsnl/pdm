#ifndef INCLUDED_PDM_FEEDBACK_LETTER_HH
#define INCLUDED_PDM_FEEDBACK_LETTER_HH

#include <string>
#include <vector>
#include <ostream>

#include "severity.hh"

namespace pdm::feedback {

    class Note;

    class Letter {
      private:
        Severity           m_severity;
        std::string        m_headline;
        std::string        m_more;
        std::vector<Note*> m_notes;

      public:
        Letter(Severity severity, std::string&& headline, std::string&& more, std::vector<Note*>&& notes)
        : m_severity(severity),
          m_headline(std::move(headline)),
          m_more(std::move(more)),
          m_notes(std::move(notes)) {}

        Letter(Severity severity, std::string headline, std::string more)
        : Letter(severity, std::move(headline), std::move(more), std::move(std::vector<Note*>())) {}

      public:
        Severity severity() const {
            return m_severity;
        }
        std::string const& headline() const {
            return m_headline;
        }
        std::string const& more() const {
            return m_more;
        }
        std::vector<Note*> const& notes() const {
            return m_notes;
        }

      public:
        void print(std::ostream& out);
    };

}

#endif  // INCLUDED_PDM_FEEDBACK_LETTER_HH
