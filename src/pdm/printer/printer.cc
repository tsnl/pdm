#include "printer.hh"

namespace pdm::printer {
    
    template <typename P, typename T>
    void help_print_chain(Printer* printer, std::vector<P> const& prefix, T tail) {
        printer->print_u32_char('{');
        printer->print_newline_indent();
    
        // the first N-1 prefix elements are always followed by ';' '\n'
        for (int index = 0; index < prefix.size(); index++) {
            ast::Stmt* item = prefix[index];
            printer->print_node(stmt);
            printer->print_str(";");

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
        printer->print_str(" = ");
        printer->print_node(rhs);
    }


    // todo: implement 'printer' printing methods
    void Printer::print_newline() {

    }
    void Printer::print_newline_indent() {

    }
    void Printer::print_newline_deindent() {

    }
    void Printer::print_u32_char(int ch) {

    }
    void Printer::print_str(std::string const& s) {

    }
    void Printer::print_intstr(intern::String const& s) {

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
            case ast::Kind::TypeclassStmt:
            {
                print_typeclass_stmt(dynamic_cast<ast::TypeclassStmt*>(node));
                break;
            }
            case ast::Kind::TypeStmt:
            {
                print_type_stmt(dynamic_cast<ast::TypeStmt*>(node));
                break;
            }
            case ast::Kind::EnumStmt:
            {
                print_enum_stmt(dynamic_cast<ast::EnumStmt*>(node));
                break;
            }
            case ast::Kind::FnStmt:
            {
                print_fn_stmt(dynamic_cast<ast::FnStmt*>(node));
                break;
            }
            case ast::Kind::ConstStmt:
            {
                print_const_stmt(dynamic_cast<ast::ConstStmt*>(node));
                break;
            }
            case ast::Kind::LetStmt:
            {
                print_let_stmt(dynamic_cast<ast::LetStmt*>(node));
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

            case ast::Kind::IdTypespec:
            {
                print_id_typespec(dynamic_cast<ast::IdTypespec*>(node));
                break;
            }
            case ast::Kind::PtrTypespec:
            {
                print_ptr_typespec(dynamic_cast<ast::PtrTypespec*>(node));
                break;
            }
            case ast::Kind::FnTypespec:
            {
                print_fn_typespec(dynamic_cast<ast::FnTypespec*>(node));
                break;
            }
            case ast::Kind::TCallTypespec:
            {
                print_tcall_typespec(dynamic_cast<ast::TCallTypespec*>(node));
                break;
            }
            case ast::Kind::TupleTypespec:
            {
                print_tuple_typespec(dynamic_cast<ast::TupleTypespec*>(node));
                break;
            }
            case ast::Kind::DotNameTypespec_TypePrefix:
            {
                print_dot_name_typespec_type_prefix(dynamic_cast<ast::DotNameTypespec_TypePrefix*>(node));
                break;
            }
            case ast::Kind::DotNameTypespec_ModPrefix:
            {
                print_dot_name_typespec_mod_prefix(dynamic_cast<ast::DotNameTypespec_ModPrefix*>(node));
                break;
            }
            case ast::Kind::StructTypespec:
            {
                print_struct_typespec(dynamic_cast<ast::StructTypespec*>(node));
                break;
            }

            case ast::Kind::BuiltinTypeStmt:
            {
                print_builtin_type_stmt(dynamic_cast<ast::BuiltinTypeStmt*>(node));
                break;
            }
        }
    }

    

    // scripts:
    void Printer::print_script(ast::Script* script) {
        print_str("script ");
        print_u32_char('"');
        print_str(script->source()->abs_path());
        print_u32_char('"');
        print_str(" ");
        help_print_chain(this, script->stmts(), nullptr);
    }

    // statements:
    void Printer::print_mod_stmt(ast::ModStmt* mod) {
        print_str("mod ");
        print_intstr(mod->module_name());
        print_u32_char(' ');
        help_print_chain(this, mod->defns(), nullptr);
    }
    void Printer::print_typeclass_stmt(ast::TypeclassStmt* tcs) {
        print_str("typeclass ");
        print_intstr(tcs->typeclass_name());
        print_str(" <");
        print_intstr(tcs->candidate_name());
        print_str(" ");
        print_node(tcs->candidate_typespec());
        print_str("> ");
        help_print_chain(this, tcs->conditions(), nullptr);
    }
    void Printer::print_type_stmt(ast::TypeStmt* ts) {
        print_str("type ");
        print_intstr(ts->lhs_name());
        
        switch (ts->rhs_kind())
        {
            case ast::TypeStmt::RhsKind::Typespec:
            {
                print_node(ts->opt_rhs_typespec());
                break;
            }
            case ast::TypeStmt::RhsKind::Extern:
            {
                print_str(" from ");
                print_intstr(ts->opt_rhs_ext_mod_name());
                print_u32_char(' ');
                print_u32_char('"');
                print_u8_str(ts->opt_rhs_ext_type_name());
                print_u32_char('"');
                break;
            }
        }
    }
    void Printer::print_enum_stmt(ast::EnumStmt* enm) {
        print_str("enum ");
        print_intstr(enm->name());
        print_str(" = ");

        print_newline();
        {
            for (ast::EnumStmt::Field* field: enm->fields()) {
                print_str("| ");
                print_intstr(field->name());
                if (field->has_explicit_typespecs()) {
                    print_u32_char('(');
                    for (int typespec_index = 0; typespec_index < field->typespecs().size(); typespec_index++) {
                        ast::Typespec* typespec = field->typespecs()[typespec_index];
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
    void Printer::print_fn_stmt(ast::FnStmt* fns) {
        print_str("fn ");
        print_intstr(fns->name());
        print_u32_char(' ');
        
        for (ast::TPattern* tpattern: fns->tpatterns()) {
            print_node(tpattern);
            print_u32_char(' ');
        }

        print_node(fns->vpattern());

        if (fns->opt_return_ts()) {
            print_str(" -> ");
            print_node(fns->opt_return_ts());
        }

        switch (fns->rhs_kind()) {
            case ast::FnStmt::RhsKind::Exp:
            {
                print_str(" = ");
                print_node(fns->opt_rhs_exp());
                break;
            }
            case ast::FnStmt::RhsKind::Extern:
            {
                print_str(" from ");
                print_intstr(fns->opt_rhs_ext_mod_name());
                print_u32_char(' ');
                print_u32_char('"');
                print_u8_str(fns->opt_rhs_ext_fn_name());
                print_u32_char('"');
            }
        }
    }
    void Printer::print_const_stmt(ast::ConstStmt* node) {
        help_print_bind_stmt(this, "const", node->lhs_lpattern(), node->rhs_exp());
    }
    void Printer::print_let_stmt(ast::LetStmt* node) {
        help_print_bind_stmt(this, "let", node->lhs_lpattern(), node->rhs_exp());
    }
    void Printer::print_var_stmt(ast::VarStmt* node) {
        help_print_bind_stmt(this, "var", node->lhs_lpattern(), node->rhs_exp());
    }
    void Printer::print_set_stmt(ast::SetStmt* node) {
        help_print_bind_stmt(this, "set", node->lhs_exp(), node->rhs_exp());
    }
    void Printer::print_discard_stmt(ast::DiscardStmt* node) {
        print_node(node->discarded_exp());
    }
    void Printer::print_extern_stmt(ast::ExternStmt* es) {
        print_str("extern ");
        print_intstr(es->ext_mod_name());
        print_u32_char(' ');
        print_node(es->link_arg());
    }
    void Printer::print_import_stmt(ast::ImportStmt* is) {
        print_str("import ");
        print_intstr(is->imported_name());
        print_str(" from ");
        print_u8_str(is->imported_from_str());
        print_str(" type ");
        print_u8_str(is->imported_type_str());
    }
    void Printer::print_using_stmt(ast::UsingStmt* node) {
        print_str("using (");
        print_node(node->used_exp());
        print_u32_char(')');
    }

    // expressions:
    void Printer::print_unit_exp(ast::UnitExp*) {
        print_str("()");
    }
    void Printer::print_int_exp(ast::IntExp* ie) {
        print_uint(ie->value(), ie->base());
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
            } else if (ch == se->quote_char()) {
                print_u32_char('\\');
                print_u32_char(se->quote_char());
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
                print_str(" :: ");
                break;
            }
            case ast::TypeQueryKind::LhsSubtypesRhs:
            {
                print_str(" :< ");
                break;
            }
            case ast::TypeQueryKind::LhsSupertypesRhs:
            {
                print_str(" >: ");
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
        print_str("fn ");
        print_node(node->lhs_vpattern());
        print_str(" = ");
        print_node(node->rhs_body());
    }
    void Printer::print_if_exp(ast::IfExp* node) {
        print_str("if ");
        print_node(node->cond_exp());
        if (node->then_exp() != nullptr) {
            print_str(" then ");
            print_node(node->then_exp());
        }
        if (node->else_exp() != nullptr) {
            print_str(" else ");
            print_node(node->else_exp());
        }
    }
    void Printer::print_dot_index_exp(ast::DotIndexExp* node) {
        print_node(node->lhs());
        print_u32_char('.');
        if (node->rhs_exp()->kind() == ast::Kind::IntExp) {
            print_node(node->rhs_exp());
        } else {
            print_u32_char('(');
            print_node(node->rhs_exp());
            print_u32_char(')');
        }
    }
    void Printer::print_dot_name_exp(ast::DotNameExp* node) {
        print_node(node->lhs());
        print_u32_char('.');
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
                print_str("not ");
                break;
            }
            default:
            {
                print_str("<UnaryOperator::?> ");
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
                print_str(" * ");
                break;
            }
            case ast::BinaryOperator::Div:
            {
                print_str(" / ");
                break;
            }
            case ast::BinaryOperator::Rem:
            {
                print_str(" % ");
                break;
            }
            case ast::BinaryOperator::Add:
            {
                print_str(" + ");
                break;
            }
            case ast::BinaryOperator::Subtract:
            {
                print_str(" - ");
                break;
            }
            case ast::BinaryOperator::Less:
            {
                print_str(" < ");
                break;
            }
            case ast::BinaryOperator::Greater:
            {
                print_str(" > ");
                break;
            }
            case ast::BinaryOperator::LessOrEq:
            {
                print_str(" <= ");
                break;
            }
            case ast::BinaryOperator::GreaterOrEq:
            {
                print_str(" >= ");
                break;
            }
            case ast::BinaryOperator::Equals:
            {
                print_str(" == ");
                break;
            }
            case ast::BinaryOperator::NotEquals:
            {
                print_str(" != ");
                break;
            }
            case ast::BinaryOperator::And:
            {
                print_str(" and ");
                break;
            }
            case ast::BinaryOperator::XOr:
            {
                print_str(" xor ");
                break;
            }
            case ast::BinaryOperator::Or:
            {
                print_str(" or ");
                break;
            }
            default:
            {
                print_str(" <BinaryOperator::?> ");
                break;
            }
        }

        print_node(node->rhs_operand());
    }
    void Printer::print_vcall_exp(ast::VCallExp* node) {
        print_node(node->lhs_called());
        print_u32_char('(');
        for (int index = 0; index < node->args().size(); index++) {
            ast::Exp* exp = node->args()[index];
            print_node(exp);
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
        for (int index = 0; index < node->args().size(); index++) {
            ast::TArg* targ = node->args()[index];
            print_node(targ);
            if (index+1 != node->args().size()) {
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
        if (node->is_singleton_pattern()) {
            ast::LPattern::Field* field = node->fields()[0];
            print_intstr(field->lhs_name());
            if (field->opt_rhs_typespec()) {
                print_u32_char(' ');
                print_node(field->opt_rhs_typespec());
            }
        } else {
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
            print_u32_char(')');
        }
    }

    // typespecs:
    void Printer::print_id_typespec(ast::IdTypespec* node) {
        print_intstr(node->name());
    }
    void Printer::print_ptr_typespec(ast::PtrTypespec* node) {
        print_u32_char('&');
        print_node(node->pointee_typespec());
    }
    void Printer::print_fn_typespec(ast::FnTypespec* node) {
        print_str("Fn ");
        print_node(node->lhs_vpattern());
        print_u32_char(' ');
        print_node(node->rhs_typespec());
    }
    void Printer::print_tcall_typespec(ast::TCallTypespec* node) {
        print_node(node->lhs_called());
        print_u32_char('[');
        int arg_count = node->args().size();
        for (int index = 0; index < arg_count; index++) {
            TArg* targ = node->args()[index];
            print_node(targ);
            if (index+1 == arg_count) {
                print_u32_char(',');
                print_u32_char(' ');
            }
        }
        print_u32_char(']');
    }
    void Printer::print_tuple_typespec(ast::TupleTypespec* node) {
        print_u32_char('(');
        int field_count = node->items().size();
        if (field_count == 1) {
            ast::Typespec* typespec = node->items()[0];
            print_node(typespec);
            print_u32_char(',');
        } else if (field_count > 1) {
            for (int index = 0; index < field_count; index++) {
                ast::Typespec* typespec = node->items()[index];
                if (index+1 != field_count) {
                    print_u32_char(',');
                    print_u32_char(' ');
                }
            }
        }
        print_u32_char(')');
    }
    void Printer::print_dot_name_typespec_type_prefix(ast::DotNameTypespec_TypePrefix* node) {
        print_node(node->lhs_typespec());
        print_u32_char('.');
        print_intstr(node->rhs_name());
    }
    void Printer::print_dot_name_typespec_mod_prefix(ast::DotNameTypespec_ModPrefix* node) {
        for (intern::String mod_name: node->lhs_prefixes()) {
            print_intstr(mod_name);
            print_u32_char('.');
        }
        print_intstr(node->rhs_name());
    }
    void Printer::print_struct_typespec(ast::StructTypespec* node) {
        print_u32_char('{');
        print_newline_indent();
        {
            int field_count = node->fields().size();
            for (int index = 0; index < field_count; index++) {
                ast::StructTypespec::Field* field = node->fields()[index];
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

    // non-syntactic elements:
    void Printer::print_builtin_type_stmt(ast::BuiltinTypeStmt* node) {
        print_str("[builtin-type ");
        print_u32_char('"');
        print_str(node->desc());
        print_u32_char('"');
        print_u32_char(']');
    }

}
