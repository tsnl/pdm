#include "interval.hh"

namespace pdm::types {

    template <typename T>
    void help_insert_interval(std::vector<Interval<T>>& intervals, Interval<T> inserted_interval) {
        // todo: insert the 'inserted_interval' into 'intervals' by
        //       unifying the two sets
        //       and maintaining 'intervals' as an **ordered**, **non-overlapping** list
    }

    void IntervalSet::insert_void_interval(VoidInterval void_interval) {
        help_insert_interval(m_void_intervals, void_interval);
    }
    void IntervalSet::insert_int_interval(IntInterval int_interval) {
        help_insert_interval(m_int_intervals, int_interval);
    }
    void IntervalSet::insert_float_interval(FloatInterval float_interval) {
        help_insert_interval(m_float_intervals, float_interval);
    }
    void IntervalSet::insert_string_interval(StringInterval string_interval) {
        help_insert_interval(m_string_intervals, string_interval);
    }
    void IntervalSet::insert_tuple_interval(TupleInterval tuple_interval) {
        help_insert_interval(m_tuple_intervals, tuple_interval);
    }
    void IntervalSet::insert_struct_interval(StructInterval struct_interval) {
        help_insert_interval(m_struct_intervals, struct_interval);
    }
    void IntervalSet::insert_enum_interval(EnumInterval enum_interval) {
        help_insert_interval(m_enum_intervals, enum_interval);
    }
    void IntervalSet::insert_fn_interval(FnInterval fn_interval) {
        help_insert_interval(m_fn_intervals, fn_interval);
    }
    void IntervalSet::insert_module_interval(ModuleInterval module_interval) {
        help_insert_interval(m_module_intervals, module_interval);
    }
}