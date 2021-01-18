#include "invariant.hh"

#include "relation.hh"

namespace pdm::types {

    bool KindInvariant::implies(Invariant const& other) {
        // e.g.
        // 1 1 0 1 vs. 1 0 0 1 => OK
        // 1 1 0 0 vs. 1 0 0 1 => Fail
        KindInvariant const* opt_kind_invariant = dynamic_cast<KindInvariant const*>(&other);
        if (opt_kind_invariant == nullptr) {
            return false;
        } else {
            KindInvariant const& other = *opt_kind_invariant;
            u64 lhs = allowed_type_kinds_bitset();
            u64 rhs = other.allowed_type_kinds_bitset();
            return (lhs | rhs) == lhs;
        }
    }

    bool SubtypeOfInvariant::implies(Invariant const& other) {
        SubtypeOfInvariant const* opt_subtype_of_invariant = dynamic_cast<SubtypeOfInvariant const*>(&other);
        if (opt_subtype_of_invariant == nullptr) {
            return false;
        } else {
            return supertype_tv() == opt_subtype_of_invariant->supertype_tv();
        }
    }
    bool SubclassOfInvariant::implies(Invariant const& other) {
        SubclassOfInvariant const* opt_subclass_of_invariant = dynamic_cast<SubclassOfInvariant const*>(&other);
        if (opt_subclass_of_invariant == nullptr) {
            return false;
        } else {
            return superclass_cv() == opt_subclass_of_invariant->superclass_cv();
        }
    }
    bool ClassOfInvariant::implies(Invariant const& other) {
        ClassOfInvariant const* opt_class_of_invariant = dynamic_cast<ClassOfInvariant const*>(&other);
        if (opt_class_of_invariant == nullptr) {
            return false;
        } else {
            return member_tv() == opt_class_of_invariant->member_tv();
        }
    }

    bool VoidInvariant::implies(Invariant const& other) {
        return dynamic_cast<VoidInvariant const*>(&other) != nullptr;
    }
    bool StringInvariant::implies(Invariant const& other) {
        return dynamic_cast<StringInvariant const*>(&other) != nullptr;
    }

    bool IntInvariant::implies(Invariant const& other) {
        IntInvariant const* opt_int_invariant = dynamic_cast<IntInvariant const*>(&other);
        if (opt_int_invariant == nullptr) {
            return false;
        } else {
            IntInvariant const& other = *opt_int_invariant;
            return (
                (uses_sign_extension() == other.uses_sign_extension()) &&
                (min_width_in_bits() <= other.min_width_in_bits()) && 
                (max_width_in_bits() >= other.max_width_in_bits())
            );
        }
    }
    bool FloatInvariant::implies(Invariant const& other) {
        FloatInvariant const* opt_float_invariant = dynamic_cast<FloatInvariant const*>(&other);
        if (opt_float_invariant == nullptr) {
            return false;
        } else {
            FloatInvariant const& other = *opt_float_invariant;
            return (
                (min_width_in_bits() <= other.min_width_in_bits()) &&
                (max_width_in_bits() <= other.max_width_in_bits())
            );
        }
    }

    bool TupleInvariant::implies(Invariant const& other) {
        TupleInvariant const* opt_tuple_invariant = dynamic_cast<TupleInvariant const*>(&other);
        if (opt_tuple_invariant == nullptr) {
            return false;
        } else {
            TupleInvariant const& other = *opt_tuple_invariant;
            if (typeof_items_tvs().size() != other.typeof_items_tvs().size()) {
                return false;
            } else {
                assert(other.typeof_items_tvs().size() == typeof_items_tvs().size());
                size_t cmp_count = other.typeof_items_tvs().size();
                for (size_t cmp_index = 0; cmp_index < cmp_count; cmp_index++) {
                    TypeVar* item_tv = typeof_items_tvs()[cmp_index];
                    TypeVar* other_item_tv = other.typeof_items_tvs()[cmp_index];
                    if (item_tv != other_item_tv) {
                        return false;
                    }
                }
                return true;
            }
        }
    }

    bool FieldCollectionInvariant::implies(Invariant const& other) {
        FieldCollectionInvariant const* opt_fielder_invariant = dynamic_cast<FieldCollectionInvariant const*>(&other);
        if (opt_fielder_invariant == nullptr) {
            return false;
        } else {
            FieldCollectionInvariant const& implied = *opt_fielder_invariant;
            if (required_type_kind() != implied.required_type_kind()) {
                return false;
            }

            // if any implied field name is not contained in this, return false.
            for (auto const& implied_it: implied.fields()) {
                intern::String field_name = implied_it.first;
                if (fields().find(field_name) == fields().end()) {
                    return false;
                }
            }
            return true;
        }
    }

    bool ArrayInvariant::implies(Invariant const& raw_other) {
        ArrayInvariant const* opt_array_invariant = dynamic_cast<ArrayInvariant const*>(&raw_other);
        if (opt_array_invariant == nullptr) {
            return false;
        } else {
            ArrayInvariant const& other = *opt_array_invariant;
            return item_tv() == other.item_tv();
        }
    }

    bool FnInvariant::implies(Invariant const& other) {
        FnInvariant const* opt_fn_invariant = dynamic_cast<FnInvariant const*>(&other);
        if (opt_fn_invariant == nullptr) {
            return false;
        } else {
            FnInvariant const& other = *opt_fn_invariant;
            return (
                formal_args() == other.formal_args() &&
                typeof_ret_tv() == other.typeof_ret_tv()
            );
        }
    }

}
