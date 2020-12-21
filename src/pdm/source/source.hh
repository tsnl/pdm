#ifndef INCLUDED_PDM_SOURCE_SOURCE_HH
#define INCLUDED_PDM_SOURCE_SOURCE_HH

#include <string>

namespace pdm::source {

    class Source {
      private:
        std::string m_abs_path;

      public:
        Source(std::string&& abs_path)
        : m_abs_path(std::move(abs_path)) {}

      public:
        std::string const& abs_path() const {
            return m_abs_path;
        }
    };

}   // namespace pdm::source

#endif  // INCLUDED_PDM_SOURCE_SOURCE_HH
