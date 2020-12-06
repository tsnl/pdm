#ifndef INCLUDED_PDM_SOURCE_SOURCE_HH
#define INCLUDED_PDM_SOURCE_SOURCE_HH

#include <string>

namespace pdm::source {

    class Source {
      private:
        std::string m_path;

      public:
        std::string const& path() const {
            return m_path;
        }
    };

}   // namespace pdm::source

#endif  // INCLUDED_PDM_SOURCE_SOURCE_HH
