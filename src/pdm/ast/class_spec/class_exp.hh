#ifndef INCLUDED__PDM__AST__CLASS_SPEC__CLASS_EXP_HH
#define INCLUDED__PDM__AST__CLASS_SPEC__CLASS_EXP_HH

#include "class_spec.hh"
#include "pdm/ast/kind.hh"
#include "pdm/source/loc.hh"
#include "pdm/core/intern.hh"

namespace pdm::types {
    class TypeVar;
    class ClassVar;
}
namespace pdm::ast {

}
namespace pdm::ast {

    class ClassExpClassSpec: public ClassSpec {
        friend Manager;

    private:
        intern::String              m_candidate_name;
        ClassSpec*                  m_candidate_class_spec;
        std::vector<TypeQueryExp*>  m_conditions;
        types::ClassVar*            m_x_defn_var;

      public:
        ClassExpClassSpec(
            source::Loc loc,
            intern::String candidate_name,
            ClassSpec* candidate_class_spec,
            std::vector<TypeQueryExp*>&& conditions
        );

      public:
        [[nodiscard]] intern::String candidate_name() const;
        [[nodiscard]] ClassSpec* candidate_class_spec() const;
        [[nodiscard]] std::vector<TypeQueryExp*> const& conditions() const;

      public:
        [[nodiscard]] types::ClassVar* x_defn_var() const;
        void x_defn_var(types::ClassVar* defn_var);
    };

    inline ClassExpClassSpec::ClassExpClassSpec(
        source::Loc loc,
        intern::String candidate_name, ClassSpec* candidate_class_spec,
        std::vector<TypeQueryExp*>&& conditions
    )
    :   ClassSpec(loc, Kind::ClassExpClassSpec),
        m_candidate_name(candidate_name),
        m_candidate_class_spec(candidate_class_spec),
        m_conditions(std::move(conditions)),
        m_x_defn_var(nullptr)
    {}

    inline types::ClassVar* ClassExpClassSpec::x_defn_var() const {
        return m_x_defn_var;
    }

    inline void ClassExpClassSpec::x_defn_var(types::ClassVar* defn_var) {
        m_x_defn_var = defn_var;
    }

    inline intern::String ClassExpClassSpec::candidate_name() const {
        return m_candidate_name;
    }

    inline ClassSpec* ClassExpClassSpec::candidate_class_spec() const {
        return m_candidate_class_spec;
    }

    inline std::vector<TypeQueryExp*> const& ClassExpClassSpec::conditions() const {
        return m_conditions;
    }


}

#endif  // INCLUDED__PDM__AST__CLASS_SPEC__CLASS_EXP_HH