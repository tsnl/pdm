#ifndef INCLUDED_PDM_CORE_UNICODER_H
#define INCLUDED_PDM_CORE_UNICODER_H

#include <cstring>
#include <sstream>
#include <vector>

#include "pdm/core/integer.hh"

namespace pdm::utf8 {

    using Char = pdm::u8;

    class String;
    class StringBuilder;

    class String {
        friend String operator+ (String&& s1, String&& s2);
        friend String operator+ (String const& s1, String const& s2);

      private:
        Char*  m_data;
        size_t m_count;

      public:
        String()
        : m_data(nullptr),
          m_count(0) {}

        String(String&& other)
        : m_data(other.m_data), m_count(other.m_count) { 
            other.m_data = nullptr;
            other.m_count = 0;
        }
        
        String(Char* mov_buf, size_t count) 
        : m_data(mov_buf), m_count(count) {}
        
        String(Char const* ro_buf, size_t count)
        : m_data(new Char[count]),
          m_count(count) {
            memcpy(m_data, ro_buf, m_count * sizeof(Char));
        }

        String(String const& other)
        : String(other.const_data(), other.size()) {}

        String(char const* ro_buf) 
        : String(reinterpret_cast<Char const*>(ro_buf), strlen(ro_buf)) {}

        ~String() {
            if (m_data != nullptr) {
                delete[] m_data;
            }
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
        std::string string() const {
            std::stringstream ss;
            for (int index = 0; index < m_count; index++) {
                Char ch = m_data[index];
                if (0 < ch && ch < 128) {
                    ss << static_cast<char>(ch);
                } else {
                    // todo: store a UTF-8 encoding instead.
                    ss << "<u?>";
                }
            }
            return ss.str();
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

    inline String operator+ (String&& s1, String&& s2) {
        // allocating a sum string:
        size_t ss_size = s1.size() + s2.size();
        Char* ss_buf = new Char[ss_size];
        String ss {ss_buf, ss_size};

        // copying bytes from s1, then s2:
        memcpy(ss.data() + 0,         s1.const_data(), s1.size());
        memcpy(ss.data() + s1.size(), s2.const_data(), s2.size());

        // (move) freeing s1, s2
        if (s1.data()) { delete[] s1.data(); s1.m_data = nullptr; s1.m_count = 0; }
        if (s2.data()) { delete[] s2.data(); s2.m_data = nullptr; s2.m_count = 0; }
        
        // returning 'ss'
        return ss;
    }

    inline String operator+ (String const& s1, String const& s2) {
        // allocating a sum string:
        size_t ss_size = s1.size() + s2.size();
        Char* ss_buf = new Char[ss_size];

        // copying bytes from s1, then s2:
        memcpy(ss_buf + 0,         s1.const_data(), s1.size());
        memcpy(ss_buf + s1.size(), s2.const_data(), s2.size());
      
        // returning 'ss':
        return {ss_buf, ss_size};
    }
}

#endif  // INCLUDED_PDM_CORE_UNICODER_H
