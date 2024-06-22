#include "structure.hpp"
#include <boost/spirit/include/qi.hpp>
#include <string>
#include <vector>
#include <variant>

namespace qi = boost::spirit::qi;

struct frz::variable_call_statement
{
    std::vector<std::string> spaces;
    std::string name;
};

struct frz::func_call_statement
{
    std::vector<std::string> spaces;
    std::string name;
    std::vector<frz::eexpr> args;
};

struct frz::eexpr_
{
    frz::eexpr eexpr;
};

struct frz::String_write
{
    std::string String;
};

struct frz::factor
{
    std::variant<frz::func_call_statement, frz::variable_call_statement, frz::eexpr_, std::string, long double> factor;
};

struct frz::mul
{
    frz::term l;
    frz::factor r;
};

struct frz::div
{
    frz::term l;
    frz::factor r;
};

struct frz::term
{
    std::variant<frz::mul, frz::div, frz::factor> term;
};

struct frz::add
{
    frz::expr l;
    frz::term r;
};

struct frz::sub
{
    frz::expr l;
    frz::term r;
};

struct frz::expr
{
    std::variant<frz::add, frz::sub, frz::term> expr;
};

struct frz::eq
{
    frz::eexpr l;
    frz::expr r;
};

struct frz::neq
{
    frz::eexpr l;
    frz::expr r;
};

struct frz::or_expr
{
    frz::eexpr l;
    frz::expr r;
};

struct frz::and_expr
{
    frz::eexpr l;
    frz::expr r;
};

struct frz::eexpr
{
    std::variant<frz::eq, frz::neq, frz::or_expr, frz::and_expr, frz::expr> eexpr;
};

struct frz::event_statement
{
    frz::variable_call_statement var;
    frz::func_call_statement func;
};

struct frz::use_statement
{
    std::string modulename;
};

struct frz::while_statement
{
    frz::eexpr expr;
    frz::program program;
};

struct frz::for_statement
{
    frz::eexpr begin;
    frz::eexpr end;
    frz::eexpr skip;
    frz::program program;
};

struct frz::if_statement
{
    frz::eexpr expr;
    frz::program program;
};

struct frz::unit_def_statement
{
    std::string name;
    std::vector<std::variant<frz::let_statement, frz::func_def_statement>> body;
};

struct frz::func_def_statement
{
    std::string name;
    std::vector<frz::ass_statement> args;
    std::string rtype;
    frz::program program;
};

struct frz::ass_statement
{
    std::string name;
    std::string type;
};

struct frz::let_statement
{
    std::string name;
    std::string type;
};

struct frz::statement
{
    std::variant<frz::let_statement,
                 frz::ass_statement,
                 frz::func_def_statement,
                 frz::unit_def_statement,
                 frz::if_statement,
                 frz::for_statement,
                 frz::while_statement,
                 frz::use_statement,
                 frz::event_statement> statement;
};

struct frz::program
{
    std::vector<frz::statement> program;
};
