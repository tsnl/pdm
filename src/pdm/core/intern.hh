#ifndef INCLUDED_PDM_CORE_INTERNSTR_HH
#define INCLUDED_PDM_CORE_INTERNSTR_HH

#include <intern/strings.h>
#include <string>

#include "integer.hh"

namespace pdm::intern {
    
    class String {
      private:
        struct Manager {
            strings* m_strings_repository;
            Manager();
            ~Manager();

            void ensure_init();
        };

        static Manager s_manager;

      private:
        u32 m_id;

      public:
        static void ensure_init();

      public:
        String() = default;
        String(String const& other) = default;
        String(char const* str);

      public:
        [[nodiscard]] char const* content() const;
        [[nodiscard]] inline std::string cpp_str() const;

      public:
        inline bool operator== (String const& other) const {
            return m_id == other.m_id;
        }

        inline bool operator< (String const& other) const {
            return m_id < other.m_id;
        }
        inline bool operator> (String const& other) const {
            return m_id > other.m_id;
        }
        inline bool operator<= (String const& other) const {
            return m_id <= other.m_id;
        }
        inline bool operator>= (String const& other) const {
            return m_id >= other.m_id;
        }
    };

    std::string String::cpp_str() const {
        return content();
    }

}

#endif  // INCLUDED_PDM_CORE_INTERNSTR_HH
