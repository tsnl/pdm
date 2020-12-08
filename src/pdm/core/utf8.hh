#ifndef INCLUDED_PDM_CORE_UNICODER_H
#define INCLUDED_PDM_CORE_UNICODER_H

#include <cstring>
#include <vector>

#include "pdm/core/integer.hh"

namespace pdm::utf8 {

    using Char = pdm::u8;

    class String;
    class StringBuilder;

    class String {
      private:
        Char*  m_data;
        size_t m_count;

      public:
        String(String&& other)
        : m_data(other.m_data), m_count(other.m_count) { 
            other.m_data = nullptr;
            other.m_count = 0;
        }
        String(String const& other) = delete;

        String(Char* mov_buf, size_t count) 
        : m_data(mov_buf), m_count(count) {}
        
        String(Char const* ro_buf, size_t count)
        : m_data(new Char[count]),
          m_count(count) {
            memcpy(m_data, ro_buf, m_count * sizeof(Char));
        }

        String(char const* ro_buf) 
        : String(reinterpret_cast<Char const*>(ro_buf), strlen(ro_buf)) {}

        ~String() {
            delete[] m_data;
        }

      public:
        size_t size() const {
            return m_count;
        }
        Char const* const_data() const {
            return m_data;
        }
        Char* data() {
            return m_data;
        }
    };

    class StringBuilder {
      private:
        std::vector<Char> m_chars;

      public:
        StringBuilder(int min_capacity = 8) {
            m_chars.reserve(min_capacity);
        }

      public:
        void append_byte(Char ch) {
            m_chars.push_back(ch);
        }

        void append_u32(int u32_codepoint);

        void append_str(String const& str) {
            for (i64 index = 0; index < str.size(); index++) {
                m_chars.push_back(str.const_data()[index]);
            }
        }

      public:
        String strdup() {
            return String(static_cast<Char const*>(m_chars.data()), m_chars.size());
        }
    };
}

#endif  // INCLUDED_PDM_CORE_UNICODER_H
