#include "invariant.hh"

#include "relation.hh"

namespace pdm::types {

    void KindInvariant::print(printer::Printer& printer) const {
        printer.print_cstr("KindInvariant: ");
        for (TypeKindBitset tk_mask = 1; tk_mask <= static_cast<TypeKindBitset>(TypeKind::META_Max); tk_mask <<= 1) {
            if (m_allowed_type_kinds_bitset & tk_mask) {
                printer.print_cstr("| ");
                printer.print_cstr(type_kind_as_str(static_cast<TypeKind>(tk_mask)));

                if (tk_mask * 2 <= m_allowed_type_kinds_bitset) {
                    printer.print_cstr(" ");
                }
            }
        }
    };

    void SubtypeOfInvariant::print(printer::Printer& printer) const {
        printer.print_cstr("SubtypeOfInvariant: ");
        m_supertype_tv->print_title(printer);
    }

    void SubclassOfInvariant::print(printer::Printer &printer) const {
        printer.print_cstr("SubclassOfInvariant: ");
        m_superclass_cv->print_title(printer);
    }

    void ClassOfInvariant::print(printer::Printer &printer) const {
        printer.print_cstr("ClassOfInvariant: ");
        m_member_tv->print_title(printer);
    }

    void IsVoidInvariant::print(printer::Printer &printer) const {
        printer.print_cstr("(KD) IsVoidInvariant");
    }

    void IsStringInvariant::print(printer::Printer &printer) const {
        printer.print_cstr("(KD) IsStringInvariant");
    }

    void IsIntInvariant::print(printer::Printer &printer) const {
        printer.print_cstr("(KD) IsIntInvariant[");
        if (m_uses_sign_extension) {
            printer.print_cstr("signed,");
        } else {
            printer.print_cstr("unsigned,");
        }
        if (m_max_width_in_bits >= 0) {
            printer.print_uint_dec(m_min_width_in_bits);
        }
        printer.print_cstr(":");
        if (m_max_width_in_bits >= 0) {
            printer.print_uint_dec(m_max_width_in_bits);
        }
        printer.print_cstr("]");
    }

    void IsFloatInvariant::print(printer::Printer &printer) const {
        printer.print_cstr("(KD) IsFloatInvariant[");
        if (m_max_width_in_bits >= 0) {
            printer.print_uint_dec(m_min_width_in_bits);
        }
        printer.print_cstr(":");
        if (m_max_width_in_bits >= 0) {
            printer.print_uint_dec(m_max_width_in_bits);
        }
        printer.print_cstr("]");
    }

    void IsTupleInvariant::print(printer::Printer &printer) const {
        printer.print_cstr("(KD) IsTupleInvariant[length=");
        printer.print_uint_dec(m_typeof_items_tvs.size());
        printer.print_cstr("]");
    }

    void IsStructInvariant::print(printer::Printer &printer) const {
        printer.print_cstr("(KD) IsStructInvariant{");
        for (auto const& field: fields()) {
            printer.print_intstr(field.first);
            printer.print_cstr(":");
            field.second->print_title(printer);
            printer.print_cstr(",");
        }
        printer.print_cstr("}");
    }

    void IsEnumInvariant::print(printer::Printer &printer) const {
        printer.print_cstr("(KD) IsEnumInvariant{");
        for (auto const& field: fields()) {
            printer.print_intstr(field.first);
            printer.print_cstr(":");
            field.second->print_title(printer);
            printer.print_cstr(",");
        }
        printer.print_cstr("}");
    }

    void IsModuleInvariant::print(printer::Printer &printer) const {
        printer.print_cstr("(KD) IsModuleInvariant{");
        for (auto const& field: fields()) {
            printer.print_intstr(field.first);
            printer.print_cstr(":");
            field.second->print_title(printer);
            printer.print_cstr(",");
        }
        printer.print_cstr("}");
    }

    void IsArrayInvariant::print(printer::Printer &printer) const {
        printer.print_cstr("(KD) IsArrayOf: ");
        m_item_tv->print(printer);
    }

    void IsVCallableInvariant::print(printer::Printer &printer) const {
        printer.print_cstr("(KD) ");
        if (m_strength == VCallInvariantStrength::Formal) {
            printer.print_cstr("Formal:");
        } else if (m_strength == VCallInvariantStrength::Actual) {
            printer.print_cstr("Actual:");
        } else {
            printer.print_cstr("Misc:");
        }
        printer.print_cstr("IsVCallable (");
        printer.print_uint_dec(m_formal_args.size());
        printer.print_cstr(") -> ");
        m_typeof_ret_tv->print(printer);
    }

//    void ?::print(printer::Printer& printer) {
//
//    };

}
