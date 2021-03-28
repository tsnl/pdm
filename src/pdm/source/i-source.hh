#ifndef INCLUDED_PDM_SOURCE_SOURCE_HH
#define INCLUDED_PDM_SOURCE_SOURCE_HH

#include <string>
#include <filesystem>

#include "source-kind.hh"


namespace pdm::scoper {
    class Frame;
}

namespace pdm::source {

    class ISource {
      private:
        SourceKind m_source_kind;

        // By initializing m_abs_path to a canonical path first, we can **initialize the string from the path.**
        // NOTE: m_abs_path_string may be a hold-over, and can be replaced by referencing std::filesystem::path instead
        // of std::string.
        std::filesystem::path m_abs_path;
        std::string m_abs_path_string;

      protected:
        explicit ISource(std::string&& abs_path, SourceKind source_kind);

      public:
        [[nodiscard]] std::string const& abs_path() const;
        [[nodiscard]] SourceKind source_kind() const;
    };

    inline ISource::ISource(std::string&& abs_path, SourceKind source_kind)
    :   m_abs_path(std::filesystem::canonical(std::filesystem::path{std::move(abs_path)})),
        m_abs_path_string(m_abs_path.string()),
        m_source_kind(source_kind)
    {}

    inline std::string const& ISource::abs_path() const {
        return m_abs_path_string;
    }

    inline SourceKind ISource::source_kind() const {
        return m_source_kind;
    }

}   // namespace pdm::source

#endif  // INCLUDED_PDM_SOURCE_SOURCE_HH
