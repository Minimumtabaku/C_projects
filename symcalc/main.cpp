#include "cmdline.hpp" // parse_command
#include "app.hpp" // handle_expr_line
#include <expr.hpp>
int main(int argc, char *argv[])
{
    std::string test = "1+2/3*(12+1)";
    create_expression_tree(test);
    return 0;
}
