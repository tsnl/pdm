#ifndef INCLUDED_PDM_SOURCE_SOURCE_HH
#define INCLUDED_PDM_SOURCE_SOURCE_HH

#include <string>

#include "source-kind.hh"

namespace pdm::source {

    class ISource {
      private:
        std::string m_abs_path;
        SourceKind m_source_kind;

      protected:
        explicit ISource(std::string&& abs_path, SourceKind source_kind);

      public:
        [[nodiscard]] std::string const& abs_path() const;
        [[nodiscard]] SourceKind source_kind() const;
    };

    inline ISource::ISource(std::string&& abs_path, SourceKind source_kind)
    :   m_abs_path(std::move(abs_path)),
        m_source_kind(source_kind)
    {}

    inline std::string const& ISource::abs_path() const {
        return m_abs_path;
    }

    inline SourceKind ISource::source_kind() const {
        return m_source_kind;
    }


}   // namespace pdm::source

#endif  // INCLUDED_PDM_SOURCE_SOURCE_HH
