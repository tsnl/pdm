#include "pdm/core/utf8.hh"

extern "C" {
    #include "utf8proc/utf8proc.h"
}

namespace pdm::utf8 {

    void StringBuilder::append_u32(int u32_codepoint) {
        // each sequence is at most 4 bytes long.
        u8 buf[4] = {0}; 
        int u32_codepoint_size = utf8proc_encode_char(u32_codepoint, buf);
        if (u32_codepoint_size >= 1) { m_chars.push_back(buf[0]); }
        if (u32_codepoint_size >= 2) { m_chars.push_back(buf[1]); }
        if (u32_codepoint_size >= 3) { m_chars.push_back(buf[2]); }
        if (u32_codepoint_size >= 4) { m_chars.push_back(buf[3]); }
    }

}