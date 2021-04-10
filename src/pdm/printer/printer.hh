#ifndef INCLUDED_PDM_PRINTER_PRINTER_HH
#define INCLUDED_PDM_PRINTER_PRINTER_HH

#include <ostream>
#include <string>

#include "pdm/core/intern.hh"
#include "pdm/core/integer.hh"
#include "pdm/core/utf8.hh"

namespace pdm::ast {
    class Node;
}

namespace pdm::printer {

    class Printer;

    Printer* create(std::ostream& ostream_ref, intern::String target_name);

    void print_newline(Printer* printer);
    void print_newline_indent(Printer* printer);
    void print_newline_exdent(Printer* printer);

    void print_u32_char(Printer* printer, int ch);

    void print_c_str(Printer* printer, char const* cstr);
    void print_str(Printer* printer, std::string const& s);
    void print_u8_str(Printer* printer, utf8::String const& s);
    void print_int_str(Printer* printer, intern::String const& s);

    void print_uint_dec(Printer* printer, u64 u);
    void print_uint_hex(Printer* printer, u64 u);
    void print_float(Printer* printer, long double float_val);

    void print_node(Printer* printer, ast::Node* node);

    void print_json_list(
        Printer* printer,
        std::vector<std::string> const& list
    );

    void print_json_list_from_2_lists(
        Printer* printer,
        std::vector<std::string> const& list1,
        std::vector<std::string> const& list2
    );

}

#endif  // INCLUDED_PDM_PRINTER_PRINTER_HH

