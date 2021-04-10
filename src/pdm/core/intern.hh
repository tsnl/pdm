#ifndef INCLUDED_PDM_CORE_INTERNSTR_HH
#define INCLUDED_PDM_CORE_INTERNSTR_HH

#include <map>
#include <string>

#include "integer.hh"

namespace pdm::intern {
    
    class String {
      private:
        class Manager {
            // todo: can be significantly optimized:
            //  - since interned strings are immutable (cannot be deleted, recycled)
            //  - push new IDs to a flat array of strings instead of using 2 maps.
            friend String;
          
          private:
            std::map<std::string const, u32> m_ids;
            std::map<u32, std::string const> m_strings;

          public:
            Manager() noexcept;
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
        String(std::string const& str);
        String(char const* str);

      public:
        [[nodiscard]] char const* content() const;
        [[nodiscard]] std::string const& cpp_str() const;

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

      public:
        inline bool is_nil() const {
            return m_id == 0;
        }
    };

}

#endif  // INCLUDED_PDM_CORE_INTERNSTR_HH
