#include "interval.hh"

#include "pdm/core/config.hh"

//
// Helper declarations:
//

namespace pdm::types {
  
    enum class IntervalUnion {
        AB,
        AV,
        AB_Then_UV,     // no overlap
        UB,
        UV_Then_AB,     // no overlap
        UV
    };

    IntervalUnion interval_union_helper(Interval ab, Interval uv);

}

//
// Implementation:
//

namespace pdm::types {
    
    bool OrderedIntervalSet::order_fits_type(Type* type) {
        if (m_intervals.empty()) {
            return true;
        } else {
            Type* type_in_ois = m_intervals.front().submost_type();
            return (
                type->test_subtypeOf(type_in_ois) ||
                type->test_supertypeOf(type_in_ois)
            );
        }
    }
    bool OrderedIntervalSet::order_fits_interval(Interval interval) {
        return order_fits_type(interval.submost_type());
    }

    void OrderedIntervalSet::add_interval(Interval new_interval) {
        if (pdm::DEBUG) {
            assert(order_fits_interval(new_interval) && "add_interval failed: mismatched Order");
        }

        // initially, the OIS is empty. Add this interval, no checks required,
        // to establish the first order relation on this set.
        if (m_intervals.empty()) {
            m_intervals.push_back(new_interval);
            return;
        }

        // inserting the new interval into the intervals vector
        // naive: just append, sort by start position, then merge overlaps
        // better: maintain sorted order: find FIRST overlapping set.
        //  - since FIRST overlapping set, can extend left (left :< right) freely and correctly.
        //  - if extend right, may merge with subsequent N intervals by selecting submost supertype (right bound)

        // the following loop finds the first old interval overlapping with the new interval,
        // updates intervals in-place without changing set length
        // and sets X_required for each post-loop operation
        std::list<Interval>::iterator first_overlapping_interval_iterator = m_intervals.end();
        bool insert_required = false;           // request insert [u,v] at requirement_arg_index, always going **immediately before** before the element that was there.
        bool merge_after_required = false;      // try and merge from `requirement_arg_index` onward (inclusive) in the new indexing scheme
        for (auto old_interval_iterator = m_intervals.begin(); old_interval_iterator != m_intervals.end(); old_interval_iterator++) {
            Interval& old_interval = *old_interval_iterator;
            
            // recall [a,b] = old_interval, [u,v] = new_interval (from order to args)
            Type* a = old_interval.submost_type();
            Type* b = old_interval.supermost_type();
            Type* u = new_interval.submost_type();
            Type* v = new_interval.supermost_type();
            bool break_from_outer_loop = true;   // assume break after this unless set otherwise
            switch (interval_union_helper(old_interval, new_interval)) {
                case IntervalUnion::AB:
                {
                    // [u,v] snugly fits within [a,b]. No change required.
                    first_overlapping_interval_iterator = old_interval_iterator;
                    break;
                }
                case IntervalUnion::AV:
                {
                    // [a,v] is the new interval (right extension) => merge required
                    new_interval.supermost_type(v);
                    merge_after_required = true;
                    first_overlapping_interval_iterator = old_interval_iterator;
                    break;
                }
                case IntervalUnion::UB:
                {
                    // [u,b] is the new interval (left extension) => no merge required
                    new_interval.submost_type(u);
                    first_overlapping_interval_iterator = old_interval_iterator;
                    break;
                }
                case IntervalUnion::UV_Then_AB:
                {
                    // [u,v] must be inserted immediately before [a,b]
                    insert_required = true;
                    first_overlapping_interval_iterator = old_interval_iterator;
                    break;
                }
                case IntervalUnion::UV:
                {
                    // [a,b] is updated to be [u,v] => left and right extension => merge required
                    old_interval.submost_type(u);
                    old_interval.supermost_type(v);
                    merge_after_required = true;
                    first_overlapping_interval_iterator = old_interval_iterator;
                    break;
                }

                // continue searching if b :< u (no overlap)
                case IntervalUnion::AB_Then_UV:
                {
                    break_from_outer_loop = false;
                    break;
                }
            }
            if (break_from_outer_loop) {
                break;
            }
        }

        // if the for loop is exhausted unsuccessfully, then insert new_interval at the end.
        // note: insert/merge not required.
        if (first_overlapping_interval_iterator == m_intervals.end()) {
            m_intervals.push_back(new_interval);
        }

        // insert required?
        if (insert_required) {
            // inserting the new interval immediately before the iterator
            first_overlapping_interval_iterator = m_intervals.insert(first_overlapping_interval_iterator, new_interval);
        }

        // merge required?
        if (insert_required || merge_after_required) {
            Interval first_overlapping_interval = *first_overlapping_interval_iterator;

            std::list<Interval>::iterator merge_scan_iterator = first_overlapping_interval_iterator;
            for (merge_scan_iterator++; merge_scan_iterator != m_intervals.end(); merge_scan_iterator++) {
                Interval merge_scan_interval = *merge_scan_iterator;
                
                bool break_from_outer_loop = false;
                switch (interval_union_helper(first_overlapping_interval, merge_scan_interval)) 
                {
                    // no change, but must continue scanning
                    case IntervalUnion::AB:
                    {
                        break;
                    }
                    
                    // right extension
                    case IntervalUnion::AV:
                    {
                        Type* v = merge_scan_interval.supermost_type();
                        first_overlapping_interval.supermost_type(v);
                        break;
                    }
                    
                    // cannot merge => break
                    case IntervalUnion::AB_Then_UV:
                    {
                        break_from_outer_loop = true;
                        break;
                    }

                    // since subtypes must be ordered and left-extension performed before, 
                    // this should never occur:
                    case IntervalUnion::UB:
                    case IntervalUnion::UV:
                    case IntervalUnion::UV_Then_AB:
                    {
                        assert(0 && "OrderedIntervalSet ordering violation detected.");
                        break;
                    }
                }
                if (break_from_outer_loop) {
                    break;
                }
            }
        }
    }

}

//
// Helper implementations:
//

namespace pdm::types {

    IntervalUnion interval_union_helper(Interval ab, Interval uv) {
        // Assume a :< b and u :< v.
        // [a,b] U [u,v] =
        // (1)  a :< u and v :< b => [a,b] is the new interval (unchanged)
        // (2)  a :< u and b :< v => 
        //      (2.i)   u :< b => overlapping => [a,v] is the new interval (right extension)
        //      (2.ii)  b :< u => non-overlapping => insert [u,v] after [a,b] (right insertion)
        //      NOTE: must compare against each Interval at i+k (if exists) to try and merge.
        // (3)  u :< a and v :< b => 
        //      (3.i)   a :< v => overlapping => [u,b] is the new interval (left extension)
        //      (3.ii)  v :< a => non-overlapping => insert [u,v] before [a,b] (left insertion)
        // (4)  u :< a and b :< v => [u,v] is the new interval (replace [a,b] with [u,v]
        //      NOTE: must compare against each Interval at i+k (if exists) to try and merge.
    
        // suppose the existing interval is [a,b]
        Type* a = ab.submost_type();
        Type* b = ab.supermost_type();

        // suppose the new interval is [u,v]
        Type* u = uv.submost_type();
        Type* v = uv.supermost_type();

        if (a->test_subtypeOf(u)) {
            // a :< u
            if (v->test_subtypeOf(b)) {
                // v :< b => (1) no change
                // [u,v] snugly fits within [a,b]. No change required.
                return IntervalUnion::AB;
            } else {
                // b :< v => (2)...
                assert(b->test_subtypeOf(v));
                if (u->test_subtypeOf(b)) {
                    // u :< b => (2.i) => [a,v] is the new interval (right extension)
                    return IntervalUnion::AV;
                } else {
                    // b :< u => (2.ii) => insert [u,v] after [a,b]
                    return IntervalUnion::AB_Then_UV;
                }
            }
        } else {
            // u :< a
            assert(u->test_subtypeOf(a));
            if (v->test_subtypeOf(b)) {
                // v :< b
                if (a->test_subtypeOf(v)) {
                    // a :< v => (3.i)
                    return IntervalUnion::UB;
                } else {
                    assert(v->test_subtypeOf(a));
                    // v :< a => (3.ii) => insert [u,v] **immediately before** [a,b] (cf insert_required)
                    return IntervalUnion::UV_Then_AB;
                }
            } else {
                // b :< v => (4)
                assert(b->test_subtypeOf(v));
                return IntervalUnion::UV;
            }
        }
    }

}