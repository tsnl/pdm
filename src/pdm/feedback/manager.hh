#ifndef INCLUDED_PDM_FEEDBACK_MANAGER_HH
#define INCLUDED_PDM_FEEDBACK_MANAGER_HH

#include <vector>
#include <ostream>

namespace pdm::feedback {

    class Letter;

    class Manager {
      private:
        static Manager s_root;

      private:
        Manager*              m_parent;
        bool                  m_visible;
        std::vector<Letter*>  m_letters;
        std::vector<Manager*> m_children;

      private:
        Manager(Manager* parent)
        : m_parent(parent),
          m_visible(true) {}

      public:
        static Manager* root();

      public:
        Manager* add_child();

      public:
        void post(Letter* letter);
        void print_all(std::ostream& out);

      public:
        bool visible() const { return m_visible; }
        void set_invisible() { m_visible = false; }
    };

}

#endif  // INCLUDED_PDM_FEEDBACK_MANAGER_HH
