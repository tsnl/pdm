#ifndef INCLUDED__PDM__TYPES__SUBSPACE_HH
#define INCLUDED__PDM__TYPES__SUBSPACE_HH

#include <vector>
#include "type.hh"

namespace pdm::types {

    template <typename T>
    class Interval {
        T* m_beg;
        T* m_end;
    };
    using VoidInterval = Interval<VoidType>;
    using IntInterval = Interval<IntType>;
    using FloatInterval = Interval<FloatType>;
    using StringInterval = Interval<StringType>;
    using TupleInterval = Interval<TupleType>;
    using StructInterval = Interval<StructType>;
    using EnumInterval = Interval<EnumType>;
    using FnInterval = Interval<FnType>;
    using ModuleInterval = Interval<ModuleType>;
    
    class IntervalSet {
      private:
        std::vector<VoidInterval> m_void_intervals;
        std::vector<IntInterval> m_int_intervals;
        std::vector<FloatInterval> m_float_intervals;
        std::vector<StringInterval> m_string_intervals;
        std::vector<TupleInterval> m_tuple_intervals;
        std::vector<StructInterval> m_struct_intervals;
        std::vector<EnumInterval> m_enum_intervals;
        std::vector<FnInterval> m_fn_intervals;
        std::vector<ModuleInterval> m_module_intervals;

      public:
        IntervalSet() = default;

      public:
        std::vector<VoidInterval> const& void_intervals() const;
        std::vector<IntInterval> const& int_intervals() const;
        std::vector<FloatInterval> const& float_intervals() const;
        std::vector<StringInterval> const& string_intervals() const;
        std::vector<TupleInterval> const& tuple_intervals() const;
        std::vector<StructInterval> const& struct_intervals() const;
        std::vector<EnumInterval> const& enum_intervals() const;
        std::vector<FnInterval> const& fn_intervals() const;
        std::vector<ModuleInterval> const& module_intervals() const;

      public:
        void insert_void_interval(VoidInterval void_interval);
        void insert_int_interval(IntInterval int_interval);
        void insert_float_interval(FloatInterval float_interval);
        void insert_string_interval(StringInterval string_interval);
        void insert_tuple_interval(TupleInterval tuple_interval);
        void insert_struct_interval(StructInterval struct_interval);
        void insert_enum_interval(EnumInterval enum_interval);
        void insert_fn_interval(FnInterval fn_interval);
        void insert_module_interval(ModuleInterval module_interval);
    };
    inline std::vector<VoidInterval> const& IntervalSet::void_intervals() const { return m_void_intervals; }
    inline std::vector<IntInterval> const& IntervalSet::int_intervals() const { return m_int_intervals; }
    inline std::vector<FloatInterval> const& IntervalSet::float_intervals() const { return m_float_intervals; }
    inline std::vector<StringInterval> const& IntervalSet::string_intervals() const { return m_string_intervals; }
    inline std::vector<TupleInterval> const& IntervalSet::tuple_intervals() const { return m_tuple_intervals; }
    inline std::vector<StructInterval> const& IntervalSet::struct_intervals() const { return m_struct_intervals; }
    inline std::vector<EnumInterval> const& IntervalSet::enum_intervals() const { return m_enum_intervals; }
    inline std::vector<FnInterval> const& IntervalSet::fn_intervals() const { return m_fn_intervals; }
    inline std::vector<ModuleInterval> const& IntervalSet::module_intervals() const { return m_module_intervals; }

}

#endif  // INCLUDED__PDM__TYPES__SUBSPACE_HH