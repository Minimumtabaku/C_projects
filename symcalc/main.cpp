#include "cmdline.hpp" // parse_command
#include "app.hpp" // handle_expr_line
#include <expr.hpp>
int main(int argc, char *argv[])
{
    std::string test = "sin(x)";
    create_expression_tree(test);
    return 0;
}
