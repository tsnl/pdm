#include "printer.hh"

namespace pdm::printer {

    template <typename P, typename T>
    void help_print_chain(Printer* printer, std::vector<P> const& prefix, T tail) {
        printer->print_u32_char('{');
        printer->print_newline_indent();

        // the first N-1 prefix elements are always followed by ';' '\n'
        for (int index = 0; index < prefix.size(); index++) {
            ast::Node* item = prefix[index];
            printer->print_node(item);
            printer->print_cstr(";");

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
        printer->print_newline_deindent();
        printer->print_u32_char('}');
    }

    void help_print_bind_stmt(Printer* printer, std::string const& prefix, ast::Node* lhs, ast::Node* rhs) {
        printer->print_str(prefix);
        printer->print_u32_char(' ');
        printer->print_node(lhs);
        printer->print_cstr(" = ");
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
    void Printer::print_newline_deindent() {
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
        print_cstr(s.c_str());
    }
    void Printer::print_u8_str(utf8::String const& s) {
        for (int index = 0; index < s.size(); index++) {
            print_u32_char(s.const_data()[index]);
        }
        // print_cstr(s.const_data());
    }
    void Printer::print_intstr(intern::String const& s) {
        char const* cstr = s.content();
        print_cstr(cstr);
    }
    void Printer::print_cstr(char const* cstr) {
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
            case ast::Kind::Script:
            {
                print_script(dynamic_cast<ast::Script*>(node));
                break;
            }
            case ast::Kind::ModStmt:
            {
                print_mod_stmt(dynamic_cast<ast::ModStmt*>(node));
                break;
            }
            case ast::Kind::ModTypeclassStmt:
            {
                print_mod_typeclass_stmt(dynamic_cast<ast::ModTypeclassStmt*>(node));
                break;
            }
            case ast::Kind::ModTypeStmt:
            {
                print_mod_type_stmt(dynamic_cast<ast::ModTypeStmt*>(node));
                break;
            }
            case ast::Kind::ModEnumStmt:
            {
                print_mod_enum_stmt(dynamic_cast<ast::ModEnumStmt*>(node));
                break;
            }
            case ast::Kind::ModValStmt:
            {
                print_mod_val_stmt(dynamic_cast<ast::ModValStmt*>(node));
                break;
            }
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

            case ast::Kind::IdSetSpec:
            {
                print_id_typespec(dynamic_cast<ast::IdSetSpec*>(node));
                break;
            }
            case ast::Kind::FnTypeSpec:
            {
                print_fn_typespec(dynamic_cast<ast::FnTypeSpec*>(node));
                break;
            }
            case ast::Kind::TCallTypeSpec:
            {
                print_tcall_typespec(dynamic_cast<ast::TCallTypeSpec*>(node));
                break;
            }
            case ast::Kind::TupleTypeSpec:
            {
                print_tuple_typespec(dynamic_cast<ast::TupleTypeSpec*>(node));
                break;
            }
            case ast::Kind::DotNameTypeSpec_ModPrefix:
            {
                print_dot_name_typespec_mod_prefix(dynamic_cast<ast::DotNameTypeSpec_ModPrefix*>(node));
                break;
            }
            case ast::Kind::StructTypeSpec:
            {
                print_struct_typespec(dynamic_cast<ast::StructTypeSpec*>(node));
                break;
            }
            case ast::Kind::ParenTypeSpec:
            {
                print_paren_typespec(dynamic_cast<ast::ParenTypeSpec*>(node));
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

            // illegal elements:
            default:
            {
                break;
            }
        }
    }



    // scripts:
    void Printer::print_script(ast::Script* script) {
        print_cstr("script ");
        print_u32_char('"');
        print_str(script->source()->abs_path());
        print_u32_char('"');
        print_cstr(" ");
        help_print_chain(this, script->stmts(), nullptr);

        // scripts are the only nodes followed by a newline.
        print_newline();
    }

    // statements:
    void Printer::print_mod_stmt(ast::ModStmt* mod) {
        print_cstr("mod ");
        print_intstr(mod->module_name());
        // todo: print targs
        print_u32_char(' ');
        help_print_chain(this, mod->defns(), nullptr);
    }
    void Printer::print_mod_typeclass_stmt(ast::ModTypeclassStmt* tcs) {
        // print_cstr("typeclass ");
        print_intstr(tcs->typeclass_name());
        
        // todo: print targs
        
        print_cstr(" <");
        print_intstr(tcs->candidate_name());
        print_cstr(" ");
        print_node(tcs->candidate_typespec());
        print_cstr("> ");
        
        help_print_chain(this, tcs->conditions(), nullptr);
    }
    void Printer::print_mod_type_stmt(ast::ModTypeStmt* ts) {
        print_intstr(ts->lhs_name());

        for (ast::TPattern* tpattern: ts->lhs_tpatterns()) {
            print_u32_char(' ');
            print_node(tpattern);
        }

        switch (ts->rhs_kind())
        {
            case ast::ModTypeStmt::RhsKind::TypeSpec:
            {
                print_str(" = ");
                print_node(ts->opt_rhs_typespec());
                break;
            }
            case ast::ModTypeStmt::RhsKind::Extern:
            {
                print_cstr(" from ");
                print_intstr(ts->opt_rhs_ext_mod_name());
                print_u32_char(' ');
                print_u32_char('"');
                print_u8_str(ts->opt_rhs_ext_type_name());
                print_u32_char('"');
                break;
            }
        }
    }
    void Printer::print_mod_enum_stmt(ast::ModEnumStmt* enm) {
        print_intstr(enm->name());

        // todo: print targs

        print_cstr(" = ");

        print_newline();
        {
            for (ast::ModEnumStmt::Field* field: enm->fields()) {
                print_cstr("| ");
                print_intstr(field->name());
                if (field->has_explicit_typespecs()) {
                    print_u32_char('(');
                    for (int typespec_index = 0; typespec_index < field->typespecs().size(); typespec_index++) {
                        ast::TypeSpec* typespec = field->typespecs()[typespec_index];
                        print_node(typespec);
                        if (typespec_index+1 != field->typespecs().size()) {
                            print_u32_char(',');
                        }
                    }
                    print_u32_char(')');
                }
                print_newline();
            }
        }
    }
    void Printer::print_mod_val_stmt(ast::ModValStmt* mod_val_stmt) {
        print_intstr(mod_val_stmt->name());
        print_u32_char(' ');

        for (ast::TPattern* tpattern: mod_val_stmt->tpatterns()) {
            print_node(tpattern);
            print_u32_char(' ');
        }

        switch (mod_val_stmt->rhs_kind()) {
            case ast::ModValStmt::RhsKind::Internal:
            {
                print_cstr("= ");
                print_node(mod_val_stmt->opt_rhs_exp());
                break;
            }
            case ast::ModValStmt::RhsKind::External:
            {
                print_cstr("from ");
                print_intstr(mod_val_stmt->opt_rhs_ext_mod_name());
                print_u32_char(' ');
                print_u32_char('"');
                print_u8_str(mod_val_stmt->opt_rhs_ext_fn_name());
                print_u32_char('"');
            }
        }
    }
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
        print_cstr("extern ");
        print_intstr(es->ext_mod_name());
        print_u32_char(' ');
        print_node(es->link_arg());
    }
    void Printer::print_import_stmt(ast::ImportStmt* is) {
        print_cstr("import ");
        print_intstr(is->import_name());
        // fixme; incorrect escapes, so hacky, but eh
        print_cstr(" from \"");
        print_u8_str(is->import_from_str());
        print_cstr("\" type \"");
        print_u8_str(is->import_type_str());
        print_u32_char('"');
    }
    void Printer::print_using_stmt(ast::UsingStmt* node) {
        print_cstr("using ");
        print_intstr(node->module_name());
        print_u32_char('.');
        print_str(node->suffix());
        print_u32_char('*');
    }

    // expressions:
    void Printer::print_unit_exp(ast::UnitExp*) {
        print_cstr("()");
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
            print_newline_deindent();
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
        print_intstr(node->name());
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
                print_intstr(field->name());
                print_u32_char(':');
                print_u32_char(' ');
                print_node(field->value());
                if (index+1 != node->fields().size()) {
                    print_u32_char(',');
                    print_newline();
                }
            }
        }
        print_newline_deindent();
        print_u32_char('}');
    }
    void Printer::print_type_query_exp(ast::TypeQueryExp* node) {
        print_node(node->lhs_typespec());

        switch (node->query_kind())
        {
            case ast::TypeQueryKind::LhsEqualsRhs:
            {
                print_cstr(" :: ");
                break;
            }
            case ast::TypeQueryKind::LhsSubtypesRhs:
            {
                print_cstr(" :< ");
                break;
            }
            case ast::TypeQueryKind::LhsSupertypesRhs:
            {
                print_cstr(" >: ");
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
            print_newline_deindent();
            print_u32_char('}');
        }
    }
    void Printer::print_lambda_exp(ast::LambdaExp* node) {
        print_cstr("fn ");
        print_node(node->lhs_vpattern());
        print_cstr(" ");
        if (node->opt_ret_typespec() != nullptr) {
            print_cstr("-> ");
            print_node(node->opt_ret_typespec());
            print_cstr(" ");
        }
        print_node(node->rhs_body());
    }
    void Printer::print_if_exp(ast::IfExp* node) {
        print_cstr("if ");
        print_node(node->cond_exp());
        if (node->then_exp() != nullptr) {
            print_cstr(" then ");
            print_node(node->then_exp());
        }
        if (node->else_exp() != nullptr) {
            print_cstr(" else ");
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
            print_cstr(" <dot-?> ");
        }
        print_intstr(node->rhs_name());
    }
    void Printer::print_module_dot_exp(ast::ModuleDotExp* node) {
        for (intern::String prefix_module_name: node->lhs_prefix_module_names()) {
            print_intstr(prefix_module_name);
            print_cstr(":");
        }
        print_intstr(node->rhs_name());
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
            case ast::UnaryOperator::GetRef:
            {
                print_u32_char('^');
                break;
            }
            case ast::UnaryOperator::DeRef:
            {
                print_u32_char('*');
                break;
            }
            case ast::UnaryOperator::Not:
            {
                print_cstr("not ");
                break;
            }
            default:
            {
                print_cstr("<UnaryOperator::?> ");
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
                print_cstr(" * ");
                break;
            }
            case ast::BinaryOperator::Div:
            {
                print_cstr(" / ");
                break;
            }
            case ast::BinaryOperator::Rem:
            {
                print_cstr(" % ");
                break;
            }
            case ast::BinaryOperator::Add:
            {
                print_cstr(" + ");
                break;
            }
            case ast::BinaryOperator::Subtract:
            {
                print_cstr(" - ");
                break;
            }
            case ast::BinaryOperator::Less:
            {
                print_cstr(" < ");
                break;
            }
            case ast::BinaryOperator::Greater:
            {
                print_cstr(" > ");
                break;
            }
            case ast::BinaryOperator::LessOrEq:
            {
                print_cstr(" <= ");
                break;
            }
            case ast::BinaryOperator::GreaterOrEq:
            {
                print_cstr(" >= ");
                break;
            }
            case ast::BinaryOperator::Equals:
            {
                print_cstr(" == ");
                break;
            }
            case ast::BinaryOperator::NotEquals:
            {
                print_cstr(" <> ");
                break;
            }
            case ast::BinaryOperator::And:
            {
                print_cstr(" and ");
                break;
            }
            case ast::BinaryOperator::XOr:
            {
                print_cstr(" xor ");
                break;
            }
            case ast::BinaryOperator::Or:
            {
                print_cstr(" or ");
                break;
            }
            default:
            {
                print_cstr(" <BinaryOperator::?> ");
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
                    print_cstr("out ");
                    break;
                }
                case ast::VArgAccessSpec::InOut:
                {
                    print_cstr("inout ");
                    break;
                }
            }

            print_intstr(field->lhs_name());
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
            print_intstr(field->lhs_name());
            print_u32_char(' ');
            print_node(field->rhs_typespec());
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
                print_intstr(field->lhs_name());
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
            print_intstr(field->lhs_name());
            if (field->opt_rhs_typespec()) {
                print_u32_char(' ');
                print_node(field->opt_rhs_typespec());
            }
        }
    }

    // typespecs:
    void Printer::print_id_typespec(ast::IdSetSpec* node) {
        print_intstr(node->name());
    }
    void Printer::print_fn_typespec(ast::FnTypeSpec* node) {
        print_cstr("Fn ");
        print_node(node->lhs_vpattern());
        print_u32_char(' ');
        print_node(node->opt_ret_typespec());
    }
    void Printer::print_tcall_typespec(ast::TCallTypeSpec* node) {
        print_node(node->lhs_called());
        print_u32_char('[');
        int arg_count = node->args().size();
        for (int index = 0; index < arg_count; index++) {
            ast::TArg* targ = node->args()[index];
            print_node(targ);
            if (index+1 != arg_count) {
                print_u32_char(',');
                print_u32_char(' ');
            }
        }
        print_u32_char(']');
    }
    void Printer::print_tuple_typespec(ast::TupleTypeSpec* node) {
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
    void Printer::print_dot_name_typespec_mod_prefix(ast::DotNameTypeSpec_ModPrefix* node) {
        for (intern::String mod_name: node->lhs_prefixes()) {
            print_intstr(mod_name);
            print_u32_char('.');
        }
        print_intstr(node->rhs_name());
    }
    void Printer::print_struct_typespec(ast::StructTypeSpec* node) {
        print_u32_char('{');
        print_newline_indent();
        {
            int field_count = node->fields().size();
            for (int index = 0; index < field_count; index++) {
                ast::StructTypeSpec::Field* field = node->fields()[index];
                print_intstr(field->lhs_name());
                print_u32_char(' ');
                print_node(field->rhs_typespec());
                if (index+1 != field_count) {
                    print_u32_char(',');
                    print_u32_char(' ');
                }
            }
        }
        print_newline_deindent();
        print_u32_char('}');
    }
    void Printer::print_paren_typespec(ast::ParenTypeSpec* node) {
        print_u32_char('(');
        print_node(node->nested_typespec());
        print_u32_char(')');
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
                print_cstr("out ");
                break;
            }
            case ast::VArgAccessSpec::InOut:
            {
                print_cstr("inout ");
                break;
            }
        }
        print_node(varg->arg_exp());
    }

    // non-syntactic elements:
    void Printer::print_builtin_type_stmt(ast::BuiltinStmt* node) {
        print_cstr("[builtin-type ");
        print_u32_char('"');
        print_str(node->desc());
        print_u32_char('"');
        print_u32_char(']');
    }

}
