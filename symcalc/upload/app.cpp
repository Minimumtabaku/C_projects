#include "expr.hpp"
#include "cmdline.hpp"

#include <iostream>

using namespace std;

void process_expr(std::ostream &os, expr initial_expr, vector<Commands::Command> const &commands) {
    expr e = std::move(initial_expr);
    for (const auto &cmd : commands) {
        using namespace Commands;
        cmd.match(
            [&](Commands::Derive const &derive) {
                e = e->derive(derive.variable);
            },
            [&](Commands::Simplify const &) {
                e = e->simplify();
            },
            [&](Commands::Evaluate const &evaluate) {
                os << e->evaluate(evaluate.variables) << std::endl;
            },
            [&](Commands::Print const &p) {
                os << e << std::endl;
            }
        );
    }
}

void handle_expr_line(std::ostream &os, std::string const &line, vector<Commands::Command> const &commands) {
    expr e = create_expression_tree(line);
    process_expr(os, e, commands);
}
