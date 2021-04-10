#include <iostream>

#include "printer.hh"
#include "pdm/ast/visitor.hh"

namespace pdm::printer {

    class Printer {
      private:
        std::ostream& m_ostream_ref;
        int           m_indent_count;
        char const*   m_indent_text;
        intern::String m_target_name;

      // constructor:
      public:
        explicit
        Printer(std::ostream& ostream_ref, intern::String target_name = {}, char const* indent_text = "    ")
        :   m_ostream_ref(ostream_ref),
            m_indent_count(0),
            m_indent_text(indent_text),
            m_target_name(target_name)
        {}

      public:
        void print_newline();
        void print_newline_indent();
        void print_newline_exdent();

        void print_u32_char(int ch);

        void print_c_str(char const* cstr);
        void print_str(std::string const& s);
        void print_u8_str(utf8::String const& s);
        void print_int_str(intern::String const& s);

        void print_uint_dec(u64 u);
        void print_uint_hex(u64 u);
        void print_float(long double float_val);

        void print_node(ast::Node* node);

        void print_json_list(
            std::vector<std::string> const& list
        );

        void print_json_list_from_2_lists(
            std::vector<std::string> const& list1,
            std::vector<std::string> const& list2
        );

      // recursive printers:
      private:

        // scripts:
        void print_script(ast::Script* script);
        void print_script_field(ast::Script::Field* field);

        // modules:
        void print_mod_exp(ast::NativeModExp* mod_exp);
        void print_mod_mod_field(ast::NativeModExp::ModuleField* field);
        void print_value_mod_field(ast::NativeModExp::ValueField* field);
        void print_type_mod_field(ast::NativeModExp::TypeField* field);
        void print_class_mod_field(ast::NativeModExp::ClassField* field);
        void print_mod_address(ast::ModAddress* mod_address);

        // statements:
        void print_const_stmt(ast::ConstStmt* node);
        void print_val_stmt(ast::ValStmt* node);
        void print_var_stmt(ast::VarStmt* node);
        void print_set_stmt(ast::SetStmt* node);
        void print_discard_stmt(ast::DiscardStmt* node);
        void print_extern_stmt(ast::ExternStmt* node);
        void print_import_stmt(ast::ImportStmt* node);
        void print_using_stmt(ast::UsingStmt* node);

        // expressions:
        void print_unit_exp(ast::UnitExp* node);
        void print_int_exp(ast::IntExp* node);
        void print_float_exp(ast::FloatExp* node);
        void print_string_exp(ast::StringExp* node);
        void print_string_exp_piece(ast::StringExp::Piece const& string_piece);
        void print_id_exp(ast::IdExp* node);
        void print_paren_exp(ast::ParenExp* node);
        void print_tuple_exp(ast::TupleExp* node);
        void print_array_exp(ast::ArrayExp* node);
        void print_struct_exp(ast::StructExp* node);
        void print_type_query_exp(ast::TypeQueryExp* node);
        void print_chain_exp(ast::ChainExp* node);
        void print_lambda_exp(ast::LambdaExp* node);
        void print_if_exp(ast::IfExp* node);
        void print_dot_index_exp(ast::DotIndexExp* node);
        void print_dot_name_exp(ast::DotNameExp* node);
        void print_module_dot_exp(ast::ModuleDotExp* node);
        void print_unary_exp(ast::UnaryExp* node);
        void print_binary_exp(ast::BinaryExp* node);
        void print_vcall_exp(ast::VCallExp* node);
        void print_tcall_exp(ast::TCallExp* node);

        // patterns:
        void print_vpattern(ast::VPattern* node);
        void print_tpattern(ast::TPattern* node);
        void print_lpattern(ast::LPattern* node);

        // type specs:
        void print_id_type_spec(ast::IdTypeSpec* node);
        void print_fn_type_spec(ast::FnTypeSpec* node);
        void print_tuple_type_spec(ast::TupleTypeSpec* node);
        void print_dot_type_spec(ast::ModAddressIdTypeSpec* node);
        void print_struct_type_spec(ast::StructTypeSpec* node);
        void print_enum_type_spec(ast::EnumTypeSpec* node);

        // class specs:
        void print_id_class_spec(ast::IdClassSpec* node);
        void print_class_exp_class_spec(ast::ClassExpClassSpec* node);

        // args:
        void print_targ(ast::TArg* targ);
        void print_varg(ast::VArg* varg);

        // non-syntactic elements:
        void print_builtin_type_stmt(ast::BuiltinStmt* node);

        // packages:
        void print_package(ast::Package* package);
        void print_package_export_field_for_extern_module_in_c(
            ast::Package::ExportField_ExternModuleInC* field
        );
        void print_package_export_field_for_import_all_modules_from(
            ast::Package::ExportField_ImportAllModulesFrom* extern_field
        );
    };

    template <typename P, typename T>
    void help_print_chain(Printer* printer, std::vector<P> const& prefix, T tail) {
        printer->print_u32_char('{');
        printer->print_newline_indent();

        // the first N-1 prefix elements are always followed by ';' '\n'
        for (int index = 0; index < prefix.size(); index++) {
            ast::Node* item = prefix[index];
            printer->print_node(item);
            printer->print_c_str(";");

            if (tail == nullptr) {
                // if no tail, need to skip last 'print_newline' for 'print_newline_deindent' later.
                if (index+1 != prefix.size()) {
                    printer->print_newline();
                }
            } else {
                // since tail present, always print newline after stmts.
                printer->print_newline();
            }
        }

        // if a tail is present, print it now:
        if (tail != nullptr) {
            printer->print_node(tail);
        }

        // de-indent, close chain:
        printer->print_newline_exdent();
        printer->print_u32_char('}');
    }

    void help_print_bind_stmt(Printer* printer, std::string const& prefix, ast::Node* lhs, ast::Node* rhs) {
        printer->print_str(prefix);
        printer->print_u32_char(' ');
        printer->print_node(lhs);
        printer->print_c_str(" = ");
        printer->print_node(rhs);
    }

    void Printer::print_newline() {
        m_ostream_ref << std::endl;

        // postfix indent:
        for (int indent_count_index = 0; indent_count_index < m_indent_count; indent_count_index++) {
            m_ostream_ref << m_indent_text;
        }
    }
    void Printer::print_newline_indent() {
        m_indent_count++;
        print_newline();
    }
    void Printer::print_newline_exdent() {
        m_indent_count--;
        print_newline();
    }

    void Printer::print_u32_char(int ch) {
        if (0 < ch && ch < 128) {
            if (ch == '\n') {
                print_newline();
            } else {
                m_ostream_ref << static_cast<char>(ch);
            }
        } else {
            m_ostream_ref << "<u?>";
        }
    }
    void Printer::print_str(std::string const& s) {
        print_c_str(s.c_str());
    }
    void Printer::print_u8_str(utf8::String const& s) {
        for (int index = 0; index < s.size(); index++) {
            print_u32_char(s.const_data()[index]);
        }
        // print_cstr(s.const_data());
    }
    void Printer::print_int_str(intern::String const& s) {
        char const* cstr = s.content();
        print_c_str(cstr);
    }
    void Printer::print_c_str(char const* cstr) {
        for (char const* cptr = cstr; *cptr; cptr++) {
            print_u32_char(*cptr);
        }
    }

    void Printer::print_uint_dec(u64 u) {
        m_ostream_ref << std::dec << u;
    }
    void Printer::print_uint_hex(u64 u) {
        m_ostream_ref << "0x" << std::hex << u << std::dec;
    }

    void Printer::print_float(long double float_val) {
        m_ostream_ref << float_val;
    }

    void Printer::print_node(ast::Node* node) {
        switch (node->kind()) {
            // scripts:
            case ast::Kind::Script:
            {
                print_script(dynamic_cast<ast::Script*>(node));
                break;
            }
            case ast::Kind::ScriptField:
            {
                print_script_field(dynamic_cast<ast::Script::Field*>(node));
                break;
            }

            // modules:
            case ast::Kind::NativeModExp:
            {
                print_mod_exp(dynamic_cast<ast::NativeModExp*>(node));
                break;
            }
            case ast::Kind::NativeModExp_ModField:
            {
                print_mod_mod_field(dynamic_cast<ast::NativeModExp::ModuleField*>(node));
                break;
            }
            case ast::Kind::NativeModExp_ValueField:
            {
                print_value_mod_field(dynamic_cast<ast::NativeModExp::ValueField*>(node));
                break;
            }
            case ast::Kind::NativeModExp_TypeField:
            {
                print_type_mod_field(dynamic_cast<ast::NativeModExp::TypeField*>(node));
                break;
            }
            case ast::Kind::NativeModExp_ClassField:
            {
                print_class_mod_field(dynamic_cast<ast::NativeModExp::ClassField*>(node));
                break;
            }
            case ast::Kind::ModAddress:
            {
                print_mod_address(dynamic_cast<ast::ModAddress*>(node));
                break;
            }

            // statements:
            case ast::Kind::ConstStmt:
            {
                print_const_stmt(dynamic_cast<ast::ConstStmt*>(node));
                break;
            }
            case ast::Kind::ValStmt:
            {
                print_val_stmt(dynamic_cast<ast::ValStmt*>(node));
                break;
            }
            case ast::Kind::VarStmt:
            {
                print_var_stmt(dynamic_cast<ast::VarStmt*>(node));
                break;
            }
            case ast::Kind::SetStmt:
            {
                print_set_stmt(dynamic_cast<ast::SetStmt*>(node));
                break;
            }
            case ast::Kind::DiscardStmt:
            {
                print_discard_stmt(dynamic_cast<ast::DiscardStmt*>(node));
                break;
            }
            case ast::Kind::ExternStmt:
            {
                print_extern_stmt(dynamic_cast<ast::ExternStmt*>(node));
                break;
            }
            case ast::Kind::ImportStmt:
            {
                print_import_stmt(dynamic_cast<ast::ImportStmt*>(node));
                break;
            }
            case ast::Kind::UsingStmt:
            {
                print_using_stmt(dynamic_cast<ast::UsingStmt*>(node));
                break;
            }

            case ast::Kind::UnitExp:
            {
                print_unit_exp(dynamic_cast<ast::UnitExp*>(node));
                break;
            }
            case ast::Kind::IntExp:
            {
                print_int_exp(dynamic_cast<ast::IntExp*>(node));
                break;
            }
            case ast::Kind::FloatExp:
            {
                print_float_exp(dynamic_cast<ast::FloatExp*>(node));
                break;
            }
            case ast::Kind::StringExp:
            {
                print_string_exp(dynamic_cast<ast::StringExp*>(node));
                break;
            }
            case ast::Kind::IdExp:
            {
                print_id_exp(dynamic_cast<ast::IdExp*>(node));
                break;
            }
            case ast::Kind::ParenExp:
            {
                print_paren_exp(dynamic_cast<ast::ParenExp*>(node));
                break;
            }
            case ast::Kind::TupleExp:
            {
                print_tuple_exp(dynamic_cast<ast::TupleExp*>(node));
                break;
            }
            case ast::Kind::ArrayExp:
            {
                print_array_exp(dynamic_cast<ast::ArrayExp*>(node));
                break;
            }
            case ast::Kind::StructExp:
            {
                print_struct_exp(dynamic_cast<ast::StructExp*>(node));
                break;
            }
            case ast::Kind::TypeQueryExp:
            {
                print_type_query_exp(dynamic_cast<ast::TypeQueryExp*>(node));
                break;
            }
            case ast::Kind::ChainExp:
            {
                print_chain_exp(dynamic_cast<ast::ChainExp*>(node));
                break;
            }
            case ast::Kind::LambdaExp:
            {
                print_lambda_exp(dynamic_cast<ast::LambdaExp*>(node));
                break;
            }
            case ast::Kind::IfExp:
            {
                print_if_exp(dynamic_cast<ast::IfExp*>(node));
                break;
            }
            case ast::Kind::DotIndexExp:
            {
                print_dot_index_exp(dynamic_cast<ast::DotIndexExp*>(node));
                break;
            }
            case ast::Kind::DotNameExp:
            {
                print_dot_name_exp(dynamic_cast<ast::DotNameExp*>(node));
                break;
            }
            case ast::Kind::ModuleDotExp:
            {
                print_module_dot_exp(dynamic_cast<ast::ModuleDotExp*>(node));
                break;
            }
            case ast::Kind::UnaryExp:
            {
                print_unary_exp(dynamic_cast<ast::UnaryExp*>(node));
                break;
            }
            case ast::Kind::BinaryExp:
            {
                print_binary_exp(dynamic_cast<ast::BinaryExp*>(node));
                break;
            }
            case ast::Kind::VCallExp:
            {
                print_vcall_exp(dynamic_cast<ast::VCallExp*>(node));
                break;
            }
            case ast::Kind::TCallExp:
            {
                print_tcall_exp(dynamic_cast<ast::TCallExp*>(node));
                break;
            }

            case ast::Kind::VPattern:
            {
                print_vpattern(dynamic_cast<ast::VPattern*>(node));
                break;
            }
            case ast::Kind::TPattern:
            {
                print_tpattern(dynamic_cast<ast::TPattern*>(node));
                break;
            }
            case ast::Kind::LPattern:
            {
                print_lpattern(dynamic_cast<ast::LPattern*>(node));
                break;
            }

            case ast::Kind::ModAddressIdClassSpec:
            {
                print_id_class_spec(dynamic_cast<ast::IdClassSpec*>(node));
                break;
            }
            case ast::Kind::IdTypeSpec:
            {
                print_id_type_spec(dynamic_cast<ast::IdTypeSpec *>(node));
                break;
            }
            case ast::Kind::FnTypeSpec:
            {
                print_fn_type_spec(dynamic_cast<ast::FnTypeSpec *>(node));
                break;
            }
            case ast::Kind::TupleTypeSpec:
            {
                print_tuple_type_spec(dynamic_cast<ast::TupleTypeSpec *>(node));
                break;
            }
            case ast::Kind::StructTypeSpec:
            {
                print_struct_type_spec(dynamic_cast<ast::StructTypeSpec*>(node));
                break;
            }
            case ast::Kind::EnumTypeSpec:
            {
                print_enum_type_spec(dynamic_cast<ast::EnumTypeSpec*>(node));
                break;
            }

            // args:
            case ast::Kind::TArg:
            {
                print_targ(dynamic_cast<ast::TArg*>(node));
                break;
            }
            case ast::Kind::VArg:
            {
                print_varg(dynamic_cast<ast::VArg*>(node));
                break;
            }

            // non-syntactic elements:
            case ast::Kind::BuiltinStmt:
            {
                print_builtin_type_stmt(dynamic_cast<ast::BuiltinStmt*>(node));
                break;
            }

            // packages:
            case ast::Kind::Package: {
                print_package(dynamic_cast<ast::Package*>(node));
                break;
            }
            case ast::Kind::PackageExportField_ExternModuleInC: {
                print_package_export_field_for_extern_module_in_c(
                    dynamic_cast<ast::Package::ExportField_ExternModuleInC*>(node)
                );
                break;
            }
            case ast::Kind::PackageExportField_ImportAllModulesFrom: {
                print_package_export_field_for_import_all_modules_from(
                    dynamic_cast<ast::Package::ExportField_ImportAllModulesFrom*>(node)
                );
                break;
            }

            // illegal elements:
            default:
            {
                assert(0 && "NotImplemented: Printer::print_node for unknown AST kind.");
                break;
            }
        }
    }



    // scripts:
    void Printer::print_script(ast::Script* script) {
        print_c_str("script ");
        print_u32_char('"');
        print_str(script->source()->abs_path_string());
        print_u32_char('"');
        print_c_str(" {");
        print_newline_indent();
        {
            for (ast::HeaderStmt* stmt: script->header_stmts()) {
                print_node(stmt);
                print_c_str(";");
                print_newline();
            }
            // print_newline();
            size_t body_count = script->body_fields().size();
            for (size_t body_index = 0; body_index < body_count; body_index++) {
                ast::Script::Field* field = script->body_fields()[body_index];
                print_node(field);
                print_c_str(";");
                
                if (1+body_index != body_count) {
                    print_newline();
                }
            }
        }
        print_newline_exdent();
        print_c_str("}");

        // scripts are the only nodes followed by a newline.
        print_newline();
    }
    void Printer::print_script_field(ast::Script::Field* node) {
        print_c_str("mod ");
        print_int_str(node->name());
        print_c_str(" ");
        print_node(node->rhs_mod_exp());
    }

    // modules:
    void Printer::print_mod_exp(ast::NativeModExp* node) {
        if (node->opt_template_pattern()) {
            print_node(node->opt_template_pattern());
            if (!node->fields().empty()) {
                print_newline();
            }
        }

        print_c_str("{");
        print_newline_indent();
        {
            size_t fields_count = node->fields().size();
            for (size_t field_index = 0; field_index < fields_count; field_index++) {
                ast::NativeModExp::Field* field = node->fields()[field_index];
                print_node(field);
                print_c_str(";");
                if (1+field_index < fields_count) {
                    print_newline();
                }
            }
        }
        print_newline_exdent();
        print_c_str("}");
    }
    void Printer::print_mod_mod_field(ast::NativeModExp::ModuleField* node) {
        print_c_str("mod ");
        print_int_str(node->name());
        print_c_str(" ");
        print_node(node->rhs_mod_exp());
    }
    void Printer::print_value_mod_field(ast::NativeModExp::ValueField* node) {
        print_int_str(node->name());
        print_c_str(" = ");
        print_node(node->rhs_exp());
    }
    void Printer::print_type_mod_field(ast::NativeModExp::TypeField* node) {
        print_int_str(node->name());
        print_c_str(" = ");
        print_node(node->rhs_type_spec());
    }
    void Printer::print_class_mod_field(ast::NativeModExp::ClassField* node) {
        print_int_str(node->name());
        print_c_str(" = ");
        print_node(node->rhs_class_spec());
    }
    void Printer::print_mod_address(ast::ModAddress* mod_address) {
        if (mod_address->opt_parent_address()) {
            print_node(mod_address->opt_parent_address());
            print_c_str("::");
        }
        print_int_str(mod_address->rhs_name());
    }

    // statements:
    void Printer::print_const_stmt(ast::ConstStmt* node) {
        help_print_bind_stmt(this, "const", node->lhs_lpattern(), node->rhs_exp());
    }
    void Printer::print_val_stmt(ast::ValStmt* node) {
        help_print_bind_stmt(this, "val", node->lhs_lpattern(), node->rhs_exp());
    }
    void Printer::print_var_stmt(ast::VarStmt* node) {
        help_print_bind_stmt(this, "var", node->lhs_lpattern(), node->rhs_exp());
    }
    void Printer::print_set_stmt(ast::SetStmt* node) {
        help_print_bind_stmt(this, "set", node->lhs_exp(), node->rhs_exp());
    }
    void Printer::print_discard_stmt(ast::DiscardStmt* node) {
        print_str("discard ");
        print_node(node->discarded_exp());
    }
    void Printer::print_extern_stmt(ast::ExternStmt* es) {
        print_c_str("package-content ");
        print_int_str(es->ext_mod_name());
        print_u32_char(' ');
        print_node(es->link_arg());
    }
    void Printer::print_import_stmt(ast::ImportStmt* is) {
        print_c_str("import ");
        print_u32_char('{');
        print_newline_indent();
        {
            size_t group_count = is->field_groups().size();
            for (size_t field_group_index = 0; field_group_index < group_count; field_group_index++) {
                auto field_group = is->field_groups()[field_group_index];

                size_t field_count = field_group->fields().size();
                for (size_t field_index = 0; field_index < field_count; field_index++) {
                    auto field = field_group->fields()[field_index];
                    print_int_str(field->import_name());

                    if (field_index + 1 < field_count) {
                        print_str(", ");
                    }
                }
                print_c_str(" from ");
                print_u32_char('"');
                {
                    // fixme; incorrect escapes, so hacky, but only in debug import printer, so eh
                    print_u8_str(field_group->from_path());
                }
                print_u32_char('"');
                print_u32_char(';');
                if (field_group_index + 1 < group_count) {
                    print_newline();
                }
            }
        }
        print_newline_exdent();
        print_u32_char('}');
    }
    void Printer::print_using_stmt(ast::UsingStmt* node) {
        print_c_str("using ");
        print_int_str(node->module_name());
        print_u32_char('.');
        print_str(node->suffix());
        print_u32_char('*');
    }

    // expressions:
    void Printer::print_unit_exp(ast::UnitExp*) {
        print_c_str("()");
    }
    void Printer::print_int_exp(ast::IntExp* ie) {
        switch (ie->base()) {
            case ast::IntExp::Base::Dec:
            {
                print_uint_dec(ie->value());
                break;
            }
            case ast::IntExp::Base::Hex:
            {
                print_uint_hex(ie->value());
                break;
            }
        }
    }
    void Printer::print_float_exp(ast::FloatExp* fe) {
        print_float(fe->value());
    }
    void Printer::print_string_exp(ast::StringExp* se) {
        int piece_count = se->pieces().size();
        if (piece_count == 1) {
            // single piece
            print_string_exp_piece(se->pieces()[0]);
        } else if (piece_count > 1) {
            // multiple pieces, multiple lines.
            print_u32_char('(');
            print_newline_indent();
            for (int index = 0; index < se->pieces().size(); index++) {
                ast::StringExp::Piece const& piece = se->pieces()[index];
                print_string_exp_piece(piece);
                if (index+1 != se->pieces().size()) {
                    print_newline();
                }
            }
            print_newline_exdent();
            print_u32_char(')');
        }
    }
    void Printer::print_string_exp_piece(ast::StringExp::Piece const& se_piece) {
        print_u32_char(se_piece.quote_char());
        int se_piece_size = se_piece.content().size();
        for (int index = 0; index < se_piece_size; index++) {
            int ch = se_piece.content().const_data()[index];
            if (ch == '\n') {
                print_u32_char('\\');
                print_u32_char('n');
            } else if (ch == '\t') {
                print_u32_char('\\');
                print_u32_char('t');
            } else if (ch == '\r') {
                print_u32_char('\\');
                print_u32_char('r');
            } else if (ch == '\0') {
                print_u32_char('\\');
                print_u32_char('\0');
            } else if (ch == se_piece.quote_char()) {
                print_u32_char('\\');
                print_u32_char(se_piece.quote_char());
            } else if (0 < ch && ch < 128) {
                print_u32_char(ch);
            } else {
                print_u32_char('\\');
                print_u32_char('u');
                // todo: actually print in UTF8, for now just printing ASCII subset.
                print_u32_char('?');
                print_u32_char('?');
                print_u32_char('?');
                print_u32_char('?');
            }
        }
        print_u32_char(se_piece.quote_char());
    }
    void Printer::print_id_exp(ast::IdExp* node) {
        print_int_str(node->name());
    }
    void Printer::print_paren_exp(ast::ParenExp* node) {
        print_u32_char('(');
        print_node(node->nested_exp());
        print_u32_char(')');
    }
    void Printer::print_tuple_exp(ast::TupleExp* node) {
        print_u32_char('(');
        for (int index = 0; index < node->items().size(); index++) {
            ast::Exp* field_exp = node->items()[index];
            print_node(field_exp);
            if (index == 0 || index+1 != node->items().size()) {
                print_u32_char(',');
                print_u32_char(' ');
            }
        }
        print_u32_char(')');
    }
    void Printer::print_array_exp(ast::ArrayExp* node) {
        print_u32_char('[');
        for (int index = 0; index < node->items().size(); index++) {
            ast::Exp* item_exp = node->items()[index];
            print_node(item_exp);
            if (index+1 != node->items().size()) {
                print_u32_char(',');
            }
        }
        print_u32_char(']');
    }
    void Printer::print_struct_exp(ast::StructExp* node) {
        print_u32_char('{');
        print_newline_indent();
        {
            for (int index = 0; index < node->fields().size(); index++) {
                ast::StructExp::Field* field = node->fields()[index];
                print_int_str(field->name());
                print_u32_char(':');
                print_u32_char(' ');
                print_node(field->value());
                if (index+1 != node->fields().size()) {
                    print_u32_char(',');
                    print_newline();
                }
            }
        }
        print_newline_exdent();
        print_u32_char('}');
    }
    void Printer::print_type_query_exp(ast::TypeQueryExp* node) {
        print_node(node->lhs_typespec());

        switch (node->query_kind())
        {
            case ast::TypeQueryKind::LhsEqualsRhs:
            {
                print_c_str(" :: ");
                break;
            }
            case ast::TypeQueryKind::LhsSubtypesRhs:
            {
                print_c_str(" :< ");
                break;
            }
            case ast::TypeQueryKind::LhsSupertypesRhs:
            {
                print_c_str(" >: ");
                break;
            }
        }

        print_node(node->rhs_typespec());
    }
    void Printer::print_chain_exp(ast::ChainExp* node) {
        if (node->prefix().empty()) {
            print_u32_char('{');
            if (node->suffix() != nullptr) {
                print_node(node->suffix());
            }
            print_u32_char('}');
        } else {
            print_u32_char('{');
            print_newline_indent();
            {
                for (int index = 0; index < node->prefix().size(); index++) {
                    ast::Stmt* stmt = node->prefix()[index];
                    print_node(stmt);
                    print_u32_char(';');
                    if (index+1 != node->prefix().size()) {
                        print_newline();
                    }
                }
                if (node->suffix() != nullptr) {
                    print_newline();
                    print_node(node->suffix());
                }
            }
            print_newline_exdent();
            print_u32_char('}');
        }
    }
    void Printer::print_lambda_exp(ast::LambdaExp* node) {
        print_c_str("anonymous_fn ");
        print_node(node->lhs_vpattern());
        print_c_str(" ");
        if (node->opt_ret_typespec() != nullptr) {
             print_c_str("-> ");
            print_node(node->opt_ret_typespec());
            print_c_str(" ");
        }
        print_node(node->rhs_body());
    }
    void Printer::print_if_exp(ast::IfExp* node) {
        print_c_str("if ");
        print_node(node->cond_exp());
        if (node->then_exp() != nullptr) {
            print_c_str(" then ");
            print_node(node->then_exp());
        }
        if (node->else_exp() != nullptr) {
            print_c_str(" else ");
            print_node(node->else_exp());
        }
    }
    void Printer::print_dot_index_exp(ast::DotIndexExp* node) {
        print_node(node->lhs());
        print_u32_char('.');
        print_node(node->rhs_exp());
    }
    void Printer::print_dot_name_exp(ast::DotNameExp* node) {
        print_node(node->lhs());
        if (node->rhs_hint() == ast::DotNameExp::RhsHint::LhsStruct) {
            print_u32_char('.');
        } else if (node->rhs_hint() == ast::DotNameExp::RhsHint::LhsEnum) {
            print_u32_char('.');
        } else {
            print_c_str(" <dot-?> ");
        }
        print_int_str(node->rhs_name());

        if (node->rhs_hint() == ast::DotNameExp::RhsHint::LhsEnum) {
            auto self = dynamic_cast<ast::EnumDotNameExp*>(node);
            assert(self);
            if (self->opt_using_arg()) {
                print_c_str(" using ");
                print_node(self->opt_using_arg());
            }
        }
    }
    void Printer::print_module_dot_exp(ast::ModuleDotExp* node) {
        if (node->lhs_mod_address()) {
            print_node(node->lhs_mod_address());
            print_c_str("::");
        }
        print_int_str(node->rhs_name());
    }
    void Printer::print_unary_exp(ast::UnaryExp* node) {
        switch (node->unary_operator())
        {
            case ast::UnaryOperator::Plus:
            {
                print_u32_char('+');
                break;
            }
            case ast::UnaryOperator::Minus:
            {
                print_u32_char('-');
                break;
            }
            case ast::UnaryOperator::Not:
            {
                print_c_str("not ");
                break;
            }
            default:
            {
                print_c_str("<UnaryOperator::?> ");
                break;
            }
        }
        print_node(node->operand());
    }
    void Printer::print_binary_exp(ast::BinaryExp* node) {
        print_node(node->lhs_operand());

        switch (node->binary_operator())
        {
            case ast::BinaryOperator::Mul:
            {
                print_c_str(" * ");
                break;
            }
            case ast::BinaryOperator::Div:
            {
                print_c_str(" / ");
                break;
            }
            case ast::BinaryOperator::Rem:
            {
                print_c_str(" % ");
                break;
            }
            case ast::BinaryOperator::Add:
            {
                print_c_str(" + ");
                break;
            }
            case ast::BinaryOperator::Subtract:
            {
                print_c_str(" - ");
                break;
            }
            case ast::BinaryOperator::Less:
            {
                print_c_str(" < ");
                break;
            }
            case ast::BinaryOperator::Greater:
            {
                print_c_str(" > ");
                break;
            }
            case ast::BinaryOperator::LessOrEq:
            {
                print_c_str(" <= ");
                break;
            }
            case ast::BinaryOperator::GreaterOrEq:
            {
                print_c_str(" >= ");
                break;
            }
            case ast::BinaryOperator::Equals:
            {
                print_c_str(" == ");
                break;
            }
            case ast::BinaryOperator::NotEquals:
            {
                print_c_str(" <> ");
                break;
            }
            case ast::BinaryOperator::And:
            {
                print_c_str(" and ");
                break;
            }
            case ast::BinaryOperator::XOr:
            {
                print_c_str(" xor ");
                break;
            }
            case ast::BinaryOperator::Or:
            {
                print_c_str(" or ");
                break;
            }
            default:
            {
                print_c_str(" <BinaryOperator::?> ");
                break;
            }
        }

        print_node(node->rhs_operand());
    }
    void Printer::print_vcall_exp(ast::VCallExp* node) {
        print_node(node->lhs_called());
        print_u32_char('(');
        for (int index = 0; index < node->args().size(); index++) {
            ast::VArg* varg = node->args()[index];
            print_node(varg);
            if (index+1 != node->args().size()) {
                print_u32_char(',');
                print_u32_char(' ');
            }
        }
        print_u32_char(')');
    }
    void Printer::print_tcall_exp(ast::TCallExp* node) {
        print_node(node->lhs_called());
        print_u32_char('[');
        int args_count = node->args().size();
        for (int index = 0; index < args_count; index++) {
            ast::TArg* targ = node->args()[index];
            print_node(targ);
            if (index+1 != args_count) {
                print_u32_char(',');
                print_u32_char(' ');
            }
        }
        print_u32_char(']');
    }

    // patterns:
    void Printer::print_vpattern(ast::VPattern* node) {
        print_u32_char('(');
        int field_count = node->fields().size();
        for (int index = 0; index < field_count; index++) {
            ast::VPattern::Field* field = node->fields()[index];

            switch (field->accepted_varg_kind()) {
                case ast::VArgAccessSpec::In:
                {
                    break;
                }
                case ast::VArgAccessSpec::Out:
                {
                    print_c_str("out ");
                    break;
                }
                case ast::VArgAccessSpec::InOut:
                {
                    print_c_str("inout ");
                    break;
                }
            }

            print_int_str(field->lhs_name());
            print_u32_char(' ');
            print_node(field->rhs_typespec());
            if (index+1 != field_count) {
                print_u32_char(',');
                print_u32_char(' ');
            }
        }
        print_u32_char(')');
    }
    void Printer::print_tpattern(ast::TPattern* node) {
        if (node->is_only_captured()) {
            print_u32_char('!');
        }
        print_u32_char('[');
        int field_count = node->fields().size();
        for (int index = 0; index < field_count; index++) {
            ast::TPattern::Field* field = node->fields()[index];
            print_int_str(field->lhs_name());
            print_u32_char(' ');
            print_node(field->rhs_set_spec());
            if (index+1 != field_count) {
                print_u32_char(',');
                print_u32_char(' ');
            }
        }
        print_u32_char(']');
    }
    void Printer::print_lpattern(ast::LPattern* node) {
        if (node->destructure()) {
            print_u32_char('(');
            int field_count = node->fields().size();
            for (int index = 0; index < field_count; index++) {
                ast::LPattern::Field* field = node->fields()[index];
                print_int_str(field->lhs_name());
                if (field->opt_rhs_typespec()) {
                    print_u32_char(' ');
                    print_node(field->opt_rhs_typespec());
                }
                if (index+1 != field_count) {
                    print_u32_char(',');
                    print_u32_char(' ');
                }
            }
            if (field_count == 1) {
                print_u32_char(',');
            }
            print_u32_char(')');
        } else {
            ast::LPattern::Field* field = node->fields()[0];
            print_int_str(field->lhs_name());
            if (field->opt_rhs_typespec()) {
                print_u32_char(' ');
                print_node(field->opt_rhs_typespec());
            }
        }
    }

    // typespecs:
    void Printer::print_id_class_spec(ast::IdClassSpec* node) {
        print_int_str(node->name());
    }
    void Printer::print_id_type_spec(ast::IdTypeSpec* node) {
        print_int_str(node->name());
    }
    void Printer::print_fn_type_spec(ast::FnTypeSpec* node) {
        print_c_str("Fn ");
        print_node(node->lhs_vpattern());
        print_u32_char(' ');
        print_node(node->opt_ret_type_spec());
    }
    void Printer::print_tuple_type_spec(ast::TupleTypeSpec* node) {
        print_u32_char('(');
        int field_count = node->items().size();
        if (field_count == 1) {
            ast::TypeSpec* typespec = node->items()[0];
            print_node(typespec);
            print_u32_char(',');
        } else if (field_count > 1) {
            for (int index = 0; index < field_count; index++) {
                ast::TypeSpec* typespec = node->items()[index];
                if (index+1 != field_count) {
                    print_u32_char(',');
                    print_u32_char(' ');
                }
            }
        }
        print_u32_char(')');
    }
    void Printer::print_struct_type_spec(ast::StructTypeSpec* node) {
        print_u32_char('{');
        print_newline_indent();
        {
            size_t field_count = node->fields().size();
            for (size_t index = 0; index < field_count; index++) {
                ast::StructTypeSpec::Field* field = node->fields()[index];
                print_int_str(field->lhs_name());
                print_u32_char(' ');
                print_node(field->rhs_typespec());
                if (index+1 < field_count) {
                    print_u32_char(',');
                    print_u32_char(' ');
                }
            }
        }
        print_newline_exdent();
        print_u32_char('}');
    }
    void Printer::print_enum_type_spec(ast::EnumTypeSpec *node) {
        print_c_str("enum ");
        print_u32_char('{');
        print_newline_indent();
        {
            size_t field_count = node->fields().size();
            for (size_t index = 0; index < field_count; index++) {
                ast::EnumTypeSpec::Field* field = node->fields()[index];
                print_int_str(field->name());
                if (field->opt_type_spec()) {
                    print_u32_char(' ');
                    print_node(field->opt_type_spec());
                }
                if (index+1 < field_count) {
                    print_u32_char(',');
                    print_newline();
                }
            }
        }
        print_newline_exdent();
        print_u32_char('}');
    }

    // args:
    void Printer::print_targ(ast::TArg* targ) {
        print_node(targ->arg_node());
    }
    void Printer::print_varg(ast::VArg* varg) {
        switch (varg->access_spec()) {
            case ast::VArgAccessSpec::In:
            {
                break;
            }
            case ast::VArgAccessSpec::Out:
            {
                print_c_str("out ");
                break;
            }
            case ast::VArgAccessSpec::InOut:
            {
                print_c_str("inout ");
                break;
            }
        }
        print_node(varg->arg_exp());
    }

    // non-syntactic elements:
    void Printer::print_builtin_type_stmt(ast::BuiltinStmt* node) {
        print_c_str("<builtin-type-def ");
        print_u32_char('"');
        print_str(node->desc());
        print_u32_char('"');
        print_u32_char('>');
    }

    void Printer::print_dot_type_spec(ast::ModAddressIdTypeSpec* node) {
        print_mod_address(node->lhs_mod_address());
        print_int_str(node->rhs_type_name());
    }

    void Printer::print_class_exp_class_spec(ast::ClassExpClassSpec* node) {
        print_c_str("typeclass [");
        print_int_str(node->candidate_name());
        print_c_str(" ");
        print_node(node->candidate_class_spec());
        print_c_str("] {");
        print_newline_indent();
        {
            size_t conditions_count = node->conditions().size();
            for (size_t index = 0; index < conditions_count; index++) {
                auto type_query_exp = node->conditions()[index];
                print_node(type_query_exp);
                print_c_str(";");
                if (index+1 != conditions_count) {
                    print_newline();
                }
            }
        }
        print_newline_exdent();
        print_c_str("}");

    }

    void Printer::print_package(ast::Package* package) {
        print_c_str("package ");
        print_u32_char('"');
        print_str(package->source()->abs_path_string());
        print_u32_char('"');
        print_c_str(" {");
        print_newline_indent();
        {
            size_t fields_count = package->exports_fields().size();
            for (size_t i = 0; i < fields_count; i++) {
                auto export_field = package->exports_fields()[i];
                print_node(export_field);
                if (i + 1 < fields_count) {
                    print_c_str(",");
                    print_newline();
                }

            }
        }
        print_newline_exdent();
        print_c_str("}");
        print_newline();
    }

    void Printer::print_package_export_field_for_extern_module_in_c(
        ast::Package::ExportField_ExternModuleInC *field
    ) {
        print_u32_char('"');
        print_int_str(field->name());
        print_u32_char('"');
        print_c_str(": {");
        print_newline_indent();
        {
            ast::Package::ExportField_ExternModuleInC::CoreCompilerArgs const&
                core_args_ref = field->core_compiler_args();

            ast::Package::ExportField_ExternModuleInC::CompilerArgs const* opt_platform_args = nullptr;
            {
                intern::String compiler_target_name = m_target_name;

                auto const& platform_args_ref = field->platform_compiler_args();

                auto active_platform_args_it = platform_args_ref.find(compiler_target_name);
                if (active_platform_args_it != platform_args_ref.end()) {
                    opt_platform_args = &active_platform_args_it->second;
                }
            }

            print_c_str("\"include\": ");
            if (opt_platform_args) {
                print_json_list_from_2_lists(
                    core_args_ref.include,
                    opt_platform_args->include
                );
            } else {
                print_json_list(core_args_ref.include);
            }
            print_c_str(",");
            print_newline();

            print_c_str("\"lib\": ");
            if (opt_platform_args) {
                print_json_list_from_2_lists(
                    core_args_ref.lib,
                    opt_platform_args->lib
                );
            } else {
                print_json_list(core_args_ref.lib);
            }
            print_c_str(",");
            print_newline();

            print_c_str("\"src\": ");
            if (opt_platform_args) {
                print_json_list_from_2_lists(
                    core_args_ref.src,
                    opt_platform_args->src
                );
            } else {
                print_json_list(core_args_ref.src);
            }
        }
        print_newline_exdent();
        print_c_str("}");
    }

    void Printer::print_package_export_field_for_import_all_modules_from(
        ast::Package::ExportField_ImportAllModulesFrom *field
    ) {
        print_u32_char('"');
        print_int_str(field->name());
        print_u32_char('"');
        print_c_str(": {");
        print_newline_indent();
        {
            print_c_str("\"path\": ");
            print_u32_char('"');
            print_c_str(field->path().c_str());
            print_u32_char('"');
        }
        print_newline_exdent();
        print_c_str("}");
    }

    void Printer::print_json_list(
        std::vector<std::string> const& list
    ) {
        if (list.empty()) {
            print_c_str("[]");
        } else {
            print_c_str("[");
            print_newline_indent();
            {
                size_t list2_count = list.size();
                for (size_t i = 0; i < list2_count; i++) {
                    auto const& s = list[i];

                    print_u32_char('"');
                    print_str(s);
                    print_u32_char('"');

                    if (i+1 < list2_count) {
                        print_c_str(",");
                        print_newline();
                    }
                }
            }
            print_newline_exdent();
            print_c_str("]");
        }
    }

    void Printer::print_json_list_from_2_lists(
        std::vector<std::string> const& list1,
        std::vector<std::string> const& list2
    ) {
        if (list1.empty() && list2.empty()) {
            print_c_str("[]");
        } else if (list2.empty()) {
            print_json_list(list1);
        } else if (list1.empty()) {
            print_json_list(list2);
        } else {
            print_c_str("[");
            print_newline_indent();
            {
                for (auto const& s: list1) {
                    print_u32_char('"');
                    print_str(s);
                    print_u32_char('"');

                    print_c_str(",");
                    print_newline();
                }
                size_t list2_count = list2.size();
                for (size_t i = 0; i < list2_count; i++) {
                    auto const& s = list2[i];

                    print_u32_char('"');
                    print_str(s);
                    print_u32_char('"');

                    if (i+1 < list2_count) {
                        print_c_str(",");
                        print_newline();
                    }
                }
            }
            print_newline_exdent();
            print_c_str("]");
        }
    }

}


namespace pdm::printer {

    Printer* create(std::ostream& ostream_ref, intern::String target_name) {
        return new Printer{ostream_ref, target_name};
    }

    void print_newline(Printer* printer) {
        printer->print_newline();
    }
    void print_newline_indent(Printer* printer) {
        printer->print_newline_indent();
    }
    void print_newline_exdent(Printer* printer) {
        printer->print_newline_exdent();
    }

    void print_u32_char(Printer* printer, int ch) {
        printer->print_u32_char(ch);
    }

    void print_c_str(Printer* printer, char const* cstr) {
        printer->print_c_str(cstr);
    }
    void print_str(Printer* printer, std::string const& s) {
        printer->print_str(s);
    }
    void print_u8_str(Printer* printer, utf8::String const& s) {
        printer->print_u8_str(s);
    }
    void print_int_str(Printer* printer, intern::String const& s) {
        printer->print_int_str(s);
    }

    void print_uint_dec(Printer* printer, u64 u) {
        printer->print_uint_dec(u);
    }
    void print_uint_hex(Printer* printer, u64 u) {
        printer->print_uint_hex(u);
    }
    void print_float(Printer* printer, long double float_val) {
        printer->print_float(float_val);
    }

    void print_node(Printer* printer, ast::Node* node) {
        printer->print_node(node);
    }

    void print_json_list(
        Printer* printer,
        std::vector<std::string> const& list
    ) {
        printer->print_json_list(list);
    }

    void print_json_list_from_2_lists(
        Printer* printer,
        std::vector<std::string> const& list1,
        std::vector<std::string> const& list2
    ) {
        printer->print_json_list_from_2_lists(list1, list2);
    }


}