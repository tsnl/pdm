#include "intern.hh"

#include <map>
#include <cstring>
#include <algorithm>
#include <limits>

namespace pdm::intern {

    //
    // Static singleton string manager:
    //

    String::Manager String::s_manager{};

    String::Manager::Manager() noexcept
    :   m_ids(),
        m_strings() {}

    void String::Manager::ensure_init() {
        // artefact: can be deleted, and no longer in use.
    }

    String::Manager::~Manager() {
        // todo: 'free' each string-- currently leaking (since only destructed at end of program).
    }

    //
    // String:
    //

    String::String(std::string const& str)
    : String() {
        auto it = s_manager.m_ids.find(str);
        if (it != s_manager.m_ids.end()) {
            m_id = it->second;
        } else {
            assert(
                s_manager.m_ids.size() < std::numeric_limits<u32>::max() &&
                "Too many interned strings-- reached maximum count."
            );
            
            u32 new_id = 1 + s_manager.m_ids.size();
            s_manager.m_ids.insert({str, new_id});
            s_manager.m_strings.insert({new_id, str});
            m_id = new_id;
        }
    }

    String::String(char const* str)
    :   String(std::string{str}) {}

    char const* String::content() const {
        return s_manager.m_strings[m_id].c_str();
    }

    std::string const& String::cpp_str() const {
        return s_manager.m_strings[m_id];
    }

    void String::ensure_init() {
        s_manager.ensure_init();
    }
    
}   // namespace pdm::intern
