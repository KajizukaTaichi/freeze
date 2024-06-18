#include "lang.hpp"

struct let_statement
{
    std::string name;
    std::string type;
    expr_t expr;
};

struct ass_statement
{
    std::string name;
    std::string type;
    expr_t expr;
};

struct func_def_statement
{
    std::string name;
    std::vector<std::string> args;
    std::string rtype;
    program program;
};

struct unit_def_statement
{
    std::string name;
    unitbody body;
};

struct if_statement
{
    expr_t expr;
    program program;
};

struct for_statement
{
    expr_t ass;
    expr_t end;
    expr_t skip;
    program program;
};

struct while_statement
{
    expr_t expr;
    program program;
};

struct use_statement
{
    std::string name;
};

struct event_statement
{
    variable_call_statement var;
    func_call_statement func;
};

struct eq
{
    expr_t lhs;
    expr_t rhs;
};

struct neq
{
    expr_t lhs;
    expr_t rhs;
};

struct gt
{
    expr_t lhs;
    expr_t rhs;
};

struct lt
{
    expr_t lhs;
    expr_t rhs;
};

struct or_expr
{
    expr_t lhs;
    expr_t rhs;
};

struct and_expr
{
    expr_t lhs;
    expr_t rhs;
};

struct add
{
    expr_t lhs;
    expr_t rhs;
};

struct sub
{
    expr_t lhs;
    expr_t rhs;
};

struct mul
{
    expr_t lhs;
    expr_t rhs;
};

struct div
{
    expr_t lhs;
    expr_t rhs;
};

struct factor
{
    std::variant<str, ll, ld, func_call_statement, variable_call_statement> value;
};

struct func_call_statement
{
    std::vector<std::string> namespaces;
    std::string name;
    std::vector<expr_t> args;
};

struct variable_call_statement
{
    std::vector<std::string> namespaces;
    std::string name;
};

struct str
{
    std::string value;
};

struct eexpr
{
    std::variant<eq, neq, or_expr, and_expr, gt, lt, expr> value;
};

struct expr
{
    std::variant<add, sub, term> value;
};

struct term
{
    std::variant<mul, div, factor> value;
};

struct program
{
    std::vector<std::variant<
        let_statement,
        ass_statement,
        func_def_statement,
        unit_def_statement,
        if_statement,
        for_statement,
        while_statement,
        use_statement,
        event_statement,
        eexpr
    >> statements;
};

