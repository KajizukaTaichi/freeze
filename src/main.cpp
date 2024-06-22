#include "structure.hpp"
#include <boost/spirit/include/qi.hpp>
#include <string>

namespace qi = boost::spirit::qi;
using iter = std::string::iterator;
using space_t = qi::space_type;

struct parser : public qi::garmmar<iter, frz::program(), space_t>
{
    // factor member
    qi::rule<iter, std::string(), space_t> String;
    qi::rule<iter, std::string(), space_t> String_write;
    qi::rule<iter, frz::eexpr(), space_t> eexpr_;
    qi::rule<iter, frz::variable_call_statement(), space_t> variable_call_statement;
    qi::rule<iter, frz::func_call_statement(), space_t> func_call_statement;
    qi::rule<iter, frz::factor(), space_t> factor;

    // term member
    qi::rule<iter, frz::mul(), space_t> mul;
    qi::rule<iter, frz::div(), space_t> div;
    qi::rule<iter, frz::term(), space_t> term;

    // expr member
    qi::rule<iter, frz::add(), space_t> add;
    qi::rule<iter, frz::sub(), space_t> sub;
    qi::rule<iter, frz::expr(), space_t> expr;

    // eexpr member
    qi::rule<iter, frz::eq(), space_t> eq;
    qi::rule<iter, frz::neq(), space_t> neq;
    qi::rule<iter, frz::and_expr(), space_t> and_expr;
    qi::rule<iter, frz::or_expr(), space_t> or_expr;
    qi::rule<iter, frz::eexpr(), space_t> eexpr;

    // statement member
    qi::rule<iter, frz::use_statement(), space_t> use_statement;
    qi::rule<iter, frz::event_statement(), space_t> event_statement;
    qi::rule<iter, frz::while_statement(), space_t> while_statement;
    qi::rule<iter, frz::for_statement(), space_t> for_statement;
    qi::rule<iter, frz::if_statement(), space_t> if_statement;
    qi::rule<iter, frz::unit_def_statement(), space_t> unit_def_statement;
    qi::rule<iter, frz::func_def_statement(), space_t> func_def_statement;
    qi::rule<iter, frz::ass_statement(), space_t> ass_statement;
    qi::rule<iter, frz::let_statement(), space_t> let_statement;
    qi::rule<iter, frz::statement(), space_t> statement;

    // program
    qi::rule<iter, frz::program(), space_t> program;

    parser() : parser::base_type(program)
    {
        String = +(qi::standard::char_);
        String_write = qi::lit("\"") >> String >> qi::lit("\"");
        eexpr_ = qi::lit("(") >> eexpr >> qi::lit(")");
        variable_call_statement = qi::lit("$") >> *(String >> qi::lit(".")) >> String;
        func_call_statement = *(String >> qi::lit(".")) >> String >> qi::lit("(") >> *(eexpr >> ",") >> qi::lit(")");
        factor = String | String_write | eexpr_ | variable_call_statement | func_call_statement;
    }
};
