extern "C" {
    #include <intern/strings.h>
}

#include "intern.hh"

namespace pdm::intern {
        
    //
    // Manager:
    //

    Manager::Manager()
    : m_strings_repository(strings_new()) {}

    String Manager::new_str(char const* c_str) {
        return String(this, strings_intern(strings_repository(), c_str));
    }

    //
    // String:
    //

    String::String(Manager* manager, u32 id)
    : m_manager(manager),
      m_id(id) {}

    char const* String::str() const {
        return strings_lookup_id(m_manager->strings_repository(), m_id);
    }
    

    // void InitSymbols(void) {
    //     if (!stringsRepository) {
    //         stringsRepository = strings_new();
    //     }
    // }

    // void DeInitSymbols(void) {
    //     if (stringsRepository) {
    //         strings_free(stringsRepository);
    //         stringsRepository = NULL;
    //     }
    // }

    // SymbolID Symbol(char const* text) {
    //     return strings_intern(stringsRepository, text);
    // }

    // char const* GetSymbolText(SymbolID symbolID) {
    //     return strings_lookup_id(stringsRepository, symbolID);
    // }

}