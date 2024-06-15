#pragma once

#include <boost/spirit/include/qi.hpp>
#include <string>
#include <variant>

struct let_statement;
struct ass_statement;
struct func_def_statement;
struct unit_def_statement;
struct if_statement;
struct for_statement;
struct while_statement;
struct use_statement;
struct event_statement;
struct eexpr;
struct expr;
struct term;
struct factor;
struct func_call_statement;
struct variable_call_statement;

namespace qi = boost::spirit::qi;
using ll = long long;
using ld = long double;
using expr_t = std::variant<ll, ld, std::string, func_call_statement>;
using unitbody = std::variant<func_def_statement, let_statement, unit_def_statement>;
