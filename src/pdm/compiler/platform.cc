#include "platform.hh"

#include <vector>
#include <set>

#include "pdm/core/intern.hh"

namespace pdm {

    struct Singleton {
        std::vector<intern::String> platform_strings_vec;
        std::set<intern::String> platform_strings_set;

        Singleton() noexcept
        : platform_strings_vec(),
          platform_strings_set() {
            intern::String::ensure_init();

            // first, initializing the vector:
            platform_strings_vec.reserve(10);

            platform_strings_vec.emplace_back("windows-x86");
            platform_strings_vec.emplace_back("windows-amd64");
            platform_strings_vec.emplace_back("windows-arm64");
            platform_strings_vec.emplace_back("macos-amd64");
            platform_strings_vec.emplace_back("macos-arm64");
            platform_strings_vec.emplace_back("linux-x86");
            platform_strings_vec.emplace_back("linux-amd64");
            platform_strings_vec.emplace_back("linux-arm64");
            platform_strings_vec.emplace_back("wasi");

            // then, initializing other containers using the 'vec' iterators:
            platform_strings_set = {platform_strings_vec.begin(), platform_strings_vec.end()};
        }
    };

    static Singleton* singleton = nullptr;

    void ensure_init() {
        if (!singleton) {
            singleton = new Singleton{};
            assert(singleton && "Failed to allocate Platform singleton.");
        }
    }

    bool validate_platform_string(intern::String platform_string) {
        ensure_init();
        return singleton->platform_strings_set.find(platform_string) != singleton->platform_strings_set.end();
    }

    std::vector<intern::String> const &platform_strings() {
        ensure_init();
        return singleton->platform_strings_vec;
    }

}
