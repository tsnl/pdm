#include "var_invariant.hh"

#include "relation.hh"

namespace pdm::types {

    void SubtypeOfInvariant::print(printer::Printer& printer) const {
        printer.print_c_str("SubtypeOfInvariant: ");
        m_supertype_tv->print_title(printer);
    }

    void SubclassOfInvariant::print(printer::Printer &printer) const {
        printer.print_c_str("SubclassOfInvariant: ");
        m_superclass_cv->print_title(printer);
    }

    void ClassOfInvariant::print(printer::Printer &printer) const {
        printer.print_c_str("ClassOfInvariant: ");
        m_member_tv->print_title(printer);
    }

    void IsNumberVarInvariant::print(printer::Printer& printer) const {
        printer.print_c_str("IsNumberInvariant");
    }

    void IsVoidInvariant::print(printer::Printer &printer) const {
        printer.print_c_str("(KD) IsVoidInvariant");
    }

    void IsStringInvariant::print(printer::Printer &printer) const {
        printer.print_c_str("(KD) IsStringInvariant");
    }

    void IsIntInvariant::print(printer::Printer &printer) const {
        printer.print_c_str("(KD) IsIntInvariant[");
        if (m_uses_sign_extension) {
            printer.print_c_str("signed,");
        } else {
            printer.print_c_str("unsigned,");
        }
        if (m_max_width_in_bits >= 0) {
            printer.print_uint_dec(m_min_width_in_bits);
        }
        printer.print_c_str(":");
        if (m_max_width_in_bits >= 0) {
            printer.print_uint_dec(m_max_width_in_bits);
        }
        printer.print_c_str("]");
    }

    void IsFloatInvariant::print(printer::Printer &printer) const {
        printer.print_c_str("(KD) IsFloatInvariant[");
        if (m_max_width_in_bits >= 0) {
            printer.print_uint_dec(m_min_width_in_bits);
        }
        printer.print_c_str(":");
        if (m_max_width_in_bits >= 0) {
            printer.print_uint_dec(m_max_width_in_bits);
        }
        printer.print_c_str("]");
    }

    void IsTupleInvariant::print(printer::Printer &printer) const {
        printer.print_c_str("(KD) IsTupleInvariant[length=");
        printer.print_uint_dec(m_typeof_items_tvs.size());
        printer.print_c_str("]");
    }

    IsFieldCollectionInvariant::IsFieldCollectionInvariant(
        Relation* parent_relation,
        VarArchetype domain_var_kind,
        Kind required_type_kind,
        std::string name,
        std::map<intern::String, Var*>&& fields
    )
    :   KindDependentInvariant(parent_relation, domain_var_kind, required_type_kind, std::move(name)),
        m_fields(std::move(fields))
    {}

    IsStructInvariant::IsStructInvariant(
        Relation *parent_relation, VarArchetype domain_var_kind,
        std::map<intern::String, Var*> fields,
        std::string opt_name_suffix
    )
    :   IsFieldCollectionInvariant(
            parent_relation, domain_var_kind, Kind::Struct,
            "IsStruct" + (!opt_name_suffix.empty() ? ":" + std::move(opt_name_suffix) : ""),
            std::move(fields)
        )
    {}

    void IsStructInvariant::print(printer::Printer &printer) const {
        printer.print_c_str("(KD) IsStructInvariant{");
        for (auto const& field: fields()) {
            printer.print_intstr(field.first);
            printer.print_c_str(":");
            field.second->print_title(printer);
            printer.print_c_str(",");
        }
        printer.print_c_str("}");
    }

    IsEnumInvariant::IsEnumInvariant(
        Relation* parent_relation,
        VarArchetype domain_var_kind,
        std::map<intern::String, Var*> fields,
        std::string opt_name_suffix
    )
    :   IsFieldCollectionInvariant(
        parent_relation, domain_var_kind, Kind::Enum,
        "IsEnum" + (!opt_name_suffix.empty() ? ":" + std::move(opt_name_suffix) : ""),
        std::move(fields)
    )
    {}

    void IsEnumInvariant::print(printer::Printer &printer) const {
        printer.print_c_str("(KD) IsEnumInvariant{");
        for (auto const& field: fields()) {
            printer.print_intstr(field.first);
            printer.print_c_str(":");
            field.second->print_title(printer);
            printer.print_c_str(",");
        }
        printer.print_c_str("}");
    }

    IsModuleInvariant::IsModuleInvariant(
        Relation *parent_relation,
        VarArchetype domain_var_kind,
        std::map<intern::String, Var*> fields,
        std::string opt_module_name
    )
    :   IsFieldCollectionInvariant(
        parent_relation, domain_var_kind, Kind::Module,
        "IsModule" + (!opt_module_name.empty() ? ":" + std::move(opt_module_name) : ""),
        std::move(fields)
    )
    {}

    void IsModuleInvariant::print(printer::Printer &printer) const {
        printer.print_c_str("(KD) IsModuleInvariant{");
        for (auto const& field: fields()) {
            printer.print_intstr(field.first);
            printer.print_c_str(":");
            field.second->print_title(printer);
            printer.print_c_str(",");
        }
        printer.print_c_str("}");
    }

    IsArrayInvariant::IsArrayInvariant(
        Relation* parent_relation,
        VarArchetype domain_var_kind,
        TypeVar* item_tv,
        std::string array_name
    )
    :   KindDependentInvariant(parent_relation, domain_var_kind, Kind::Array, "IsArray:" + std::move(array_name)),
        m_item_tv(item_tv)
    {}

    void IsArrayInvariant::print(printer::Printer &printer) const {
        printer.print_c_str("(KD) IsArrayOf: ");
        m_item_tv->print_title(printer);
    }

    void IsVCallableInvariant::print(printer::Printer &printer) const {
        printer.print_c_str("(KD) ");
        if (m_strength == VCallInvariantStrength::Formal) {
            printer.print_c_str("Formal:");
        } else if (m_strength == VCallInvariantStrength::Actual) {
            printer.print_c_str("Actual:");
        } else {
            printer.print_c_str("Misc:");
        }
        printer.print_c_str("IsVCallable (");
        printer.print_uint_dec(m_formal_args.size());
        printer.print_c_str(") -> ");
        m_typeof_ret_tv->print_title(printer);
    }

//    void ?::print(printer::Printer& printer) {
//
//    };

}
