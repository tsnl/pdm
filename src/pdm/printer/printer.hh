#ifndef INCLUDED_PDM_PRINTER_PRINTER_HH
#define INCLUDED_PDM_PRINTER_PRINTER_HH

#include <ostream>
#include <string>

#include "pdm/ast/visitor.hh"
#include "pdm/core/intern.hh"
#include "pdm/core/integer.hh"
#include "pdm/core/utf8.hh"

namespace pdm::printer {
    
    class Printer {
      private:
        std::ostream& m_ostream_ref;
        int           m_indent_count;
        char const*   m_indent_text;

      // constructor:
      public:
        Printer(std::ostream& ostream_ref, char const* indent_text = "    ")
        :   m_ostream_ref(ostream_ref),
            m_indent_count(0),
            m_indent_text(indent_text) {}

      public:
        void print_newline();
        void print_newline_indent();
        void print_newline_exdent();
        
        void print_u32_char(int ch);
        
        void print_c_str(char const* cstr);
        void print_str(std::string const& s);
        void print_u8_str(utf8::String const& s);
        void print_intstr(intern::String const& s);

        void print_uint_dec(u64 u);
        void print_uint_hex(u64 u);
        void print_float(long double float_val);

        void print_node(ast::Node* node);

      // visit overloads:
      private:

        // scripts:
        void print_script(ast::Script* script);
        void print_script_field(ast::Script::Field* field);

        // modules:
        void print_mod_exp(ast::ModExp* mod_exp);
        void print_mod_mod_field(ast::ModExp::ModuleField* field);
        void print_value_mod_field(ast::ModExp::ValueField* field);
        void print_type_mod_field(ast::ModExp::TypeField* field);
        void print_class_mod_field(ast::ModExp::ClassField* field);
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
    };

}

#endif  // INCLUDED_PDM_PRINTER_PRINTER_HH

