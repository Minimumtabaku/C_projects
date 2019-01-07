#include "cmdline.hpp" // parse_command
#include "app.hpp" // handle_expr_line
#include <iostream>
#include <expr.hpp>
int main(int argc, char *argv[])
{
    std::string test = "(1+(((sin(x)))))";
    auto what =  create_expression_tree(test);
    std::cout << what << std::endl;
    return 0;
}
