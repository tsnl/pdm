extern "C" {
    #include <intern/strings.h>
}

#include "intern.hh"

namespace pdm::intern {

    //
    // Static String Manager:
    //

    String::Manager String::s_manager;

    String::Manager::Manager(): m_strings_repository(nullptr) {}

    void String::Manager::ensure_init() {
        if (m_strings_repository == nullptr) {
            m_strings_repository = strings_new();
        }
    }

    String::Manager::~Manager() {
        strings_free(s_manager.m_strings_repository);
        s_manager.m_strings_repository = nullptr;
    }

    //
    // String:
    //

    String::String(char const* str_content)
    : m_id(0) {
        m_id = strings_intern(s_manager.m_strings_repository, str_content);
    }

    char const* String::content() const {
        return strings_lookup_id(s_manager.m_strings_repository, m_id);
    }

    void String::ensure_init() {
        s_manager.ensure_init();
    }
    
}   // namespace pdm::intern