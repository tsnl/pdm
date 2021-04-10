#include "var-invariant.hh"

#include "relation.hh"

namespace pdm::types {

    void SubtypeOfInvariant::print(printer::Printer* printer) const {
        printer::print_c_str(printer, "SubtypeOfInvariant: ");
        m_supertype_tv->print_title(printer);
    }

    void SubclassOfInvariant::print(printer::Printer* printer) const {
        printer::print_c_str(printer, "SubclassOfInvariant: ");
        m_superclass_cv->print_title(printer);
    }

    void ClassOfInvariant::print(printer::Printer* printer) const {
        printer::print_c_str(printer, "ClassOfInvariant: ");
        m_member_tv->print_title(printer);
    }

    void IsNumberVarInvariant::print(printer::Printer* printer) const {
        printer::print_c_str(printer, "IsNumberInvariant");
    }

    void IsVoidInvariant::print(printer::Printer* printer) const {
        printer::print_c_str(printer, "(KD) IsVoidInvariant");
    }

    void IsStringInvariant::print(printer::Printer* printer) const {
        printer::print_c_str(printer, "(KD) IsStringInvariant");
    }

    void IsIntInvariant::print(printer::Printer* printer) const {
        printer::print_c_str(printer, "(KD) IsIntInvariant[");
        if (m_uses_sign_extension) {
            printer::print_c_str(printer, "signed,");
        } else {
            printer::print_c_str(printer, "unsigned,");
        }
        if (m_max_width_in_bits >= 0) {
            printer::print_uint_dec(printer, m_min_width_in_bits);
        }
        printer::print_c_str(printer, ":");
        if (m_max_width_in_bits >= 0) {
            printer::print_uint_dec(printer, m_max_width_in_bits);
        }
        printer::print_c_str(printer, "]");
    }

    void IsFloatInvariant::print(printer::Printer* printer) const {
        printer::print_c_str(printer, "(KD) IsFloatInvariant[");
        if (m_max_width_in_bits >= 0) {
            printer::print_uint_dec(printer, m_min_width_in_bits);
        }
        printer::print_c_str(printer, ":");
        if (m_max_width_in_bits >= 0) {
            printer::print_uint_dec(printer, m_max_width_in_bits);
        }
        printer::print_c_str(printer, "]");
    }

    void IsTupleInvariant::print(printer::Printer* printer) const {
        printer::print_c_str(printer, "(KD) IsTupleInvariant[length=");
        printer::print_uint_dec(printer, m_typeof_items_tvs.size());
        printer::print_c_str(printer, "]");
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

    void IsStructInvariant::print(printer::Printer* printer) const {
        printer::print_c_str(printer, "(KD) IsStructInvariant{");
        for (auto const& field: fields()) {
            printer::print_int_str(printer, field.first);
            printer::print_c_str(printer, ":");
            field.second->print_title(printer);
            printer::print_c_str(printer, ",");
        }
        printer::print_c_str(printer, "}");
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

    void IsEnumInvariant::print(printer::Printer* printer) const {
        printer::print_c_str(printer, "(KD) IsEnumInvariant{");
        for (auto const& field: fields()) {
            printer::print_int_str(printer, field.first);
            printer::print_c_str(printer, ":");
            field.second->print_title(printer);
            printer::print_c_str(printer, ",");
        }
        printer::print_c_str(printer, "}");
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

    void IsModuleInvariant::print(printer::Printer* printer) const {
        printer::print_c_str(printer, "(KD) IsModuleInvariant{");
        for (auto const& field: fields()) {
            printer::print_int_str(printer, field.first);
            printer::print_c_str(printer, ":");
            field.second->print_title(printer);
            printer::print_c_str(printer, ",");
        }
        printer::print_c_str(printer, "}");
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

    void IsArrayInvariant::print(printer::Printer* printer) const {
        printer::print_c_str(printer, "(KD) IsArrayOf: ");
        m_item_tv->print_title(printer);
    }

    void IsVCallableInvariant::print(printer::Printer* printer) const {
        printer::print_c_str(printer, "(KD) ");
        if (m_strength == VCallInvariantStrength::Formal) {
            printer::print_c_str(printer, "Formal:");
        } else if (m_strength == VCallInvariantStrength::Actual) {
            printer::print_c_str(printer, "Actual:");
        } else {
            printer::print_c_str(printer, "Misc:");
        }
        printer::print_c_str(printer, "IsVCallable (");
        printer::print_uint_dec(printer, m_formal_args.size());
        printer::print_c_str(printer, ") -> ");
        m_typeof_ret_tv->print_title(printer);
    }

//    void ?::print(printer::Printer& printer) {
//
//    };

}
