#ifndef INCLUDED__PDM__TYPES__SUBSPACE_HH
#define INCLUDED__PDM__TYPES__SUBSPACE_HH

//
// Unfortunately not in use-- will instead solve types iteratively.
// Compounds are complex to store.
//

#include <vector>
#include <deque>
#include <list>
#include <map>

#include <cassert>

#include "type.hh"

namespace pdm::types {

    class TypeSet;
    class Interval;
    class OrderedIntervalSet;
    class DisjointIntervalSet;

    // TypeSet => something we can test existence of a type within.
    class TypeSet {
      protected:
        TypeSet() = default;
        virtual ~TypeSet() = default;
    };

    // Interval represents a set of types {Y} _between_ [T,U] such that
    //  assuming T :< U,
    //    T :< Y and Y :< U
    // Compare this with the notion of an interval on the real line, [a,b], s.t x in [a,b] =>
    //    a <= x and x <= b
    // Note when T = u, T :< Y and Y :< T <=> Y = T <=> single type soln.
    // Note that T :< U required (exist on the same line)
    class Interval: public TypeSet {
      private:
        Type* m_submost_type;
        Type* m_supermost_type;

      public:
        inline Interval();
        inline Interval(Type* submost, Type* supermost);
        inline explicit Interval(Type* point);

      public:
        inline Type* submost_type() const;
        inline Type* supermost_type() const;
        inline void submost_type(Type* type);
        inline void supermost_type(Type* type);

      public:
        inline bool contains(Type* t) const;

    };
    inline Interval::Interval()
    :   Interval(nullptr, nullptr)
    {}
    inline Interval::Interval(Type* submost_type, Type* supermost_type)
    :   m_submost_type(submost_type),
        m_supermost_type(supermost_type)
    {
        // check submost :< supermost
        assert (
            submost_type->test_subtypeOf(supermost_type) &&
            "Cannot construct an Interval s.t. endpoints [T,U] do not satisfy T :< U"
        );
    }
    inline Interval::Interval(Type* point)
    :   Interval(point, point)
    {}
    inline Type* Interval::submost_type() const {
        return m_submost_type;
    }
    inline Type* Interval::supermost_type() const {
        return m_supermost_type;
    }
    inline void Interval::submost_type(Type* type) {
        m_submost_type = type;
    }
    inline void Interval::supermost_type(Type* type) {
        m_supermost_type = type;
    }
    inline bool Interval::contains(Type* t) const {
        return submost_type()->test_subtypeOf(t) && supermost_type()->test_supertypeOf(t);
    }

    // An OrderedIntervalSet is a collection of Intervals [T1,U1], [T2,U2], ...
    // such that T1 :< U1 :< T2 :< U2 :< ...
    // The existence of an ordering relation between intervals does not always hold
    // true. Thus, an OrderedIntervalSet is unique because the endpoints of intervals
    // are related by a subtyping relation.
    // NOTE: elements in (U1, T2) are NOT included in this set: not connected.
    class OrderedIntervalSet: public TypeSet {
      private:
        std::list<Interval> m_intervals;

      public:
        inline OrderedIntervalSet();

      public:
        inline Type* submost_type() const;
        inline Type* supermost_type() const;

      public:
        // add_interval unifies the given interval with this OrderedIntervalSet.
        // a runtime error occurs iff the interval does not fit in the existing order.
        void add_interval(Interval interval);
        
        // fits returns whether or not a type fits in this ordering system,
        // i.e. if type is a subtype or supertype to any of the endpoints of any of the intervals
        //      then it is a subtype or supertype to all of the endpoints of all of the intervals
        bool order_fits_type(Type* type);
        bool order_fits_interval(Interval interval);

      public:
        inline bool contains(Type* t) const;
    };
    inline OrderedIntervalSet::OrderedIntervalSet()
    :   TypeSet()
    {}
    inline Type* OrderedIntervalSet::submost_type() const {
        if (m_intervals.empty()) {
            return nullptr;
        } else {
            return m_intervals.front().submost_type();
        }
    }
    inline Type* OrderedIntervalSet::supermost_type() const {
        if (m_intervals.empty()) {
            return nullptr;
        } else {
            return m_intervals.back().supermost_type();
        }
    }
    inline bool OrderedIntervalSet::contains(Type* t) const {
        for (Interval const& interval: m_intervals) {
            if (interval.contains(t)) {
                return true;
            }
        }
        return false;
    }

}

#endif  // INCLUDED__PDM__TYPES__SUBSPACE_HH