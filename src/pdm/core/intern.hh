#ifndef INCLUDED_PDM_INTERNSTR_HH
#define INCLUDED_PDM_INTERNSTR_HH

#include <intern/strings.h>
#include <string>

#include "integer.hh"

namespace pdm::intern {
    
    class String;
    class StringManager;
    
    class String {
        friend class pdm::intern::StringManager;

      private:
        StringManager* m_manager;
        u32 m_id;

      protected:
        String(StringManager* manager, u32 id);

      public:
        char const* str() const;
    };

    class StringManager {
        friend class pdm::intern::String;

      private:
        strings* m_strings_repository;

      protected:
        strings* strings_repository() const {
            return m_strings_repository;
        }

      public:
        StringManager();

      public:
        String new_str(char const* cstr);
    };
}

#endif  // INCLUDED_PDM_INTERNSTR_HH
