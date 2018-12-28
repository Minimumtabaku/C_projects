#include "expr.hpp"
#include "expr_impl.hpp"
#include "tokenizer.hpp"
#include <stdexcept>
#include <sstream>
#include <vector>
expr expr::number(double n) {
    return std::make_shared<exprs::number>(exprs::number(n));
}

expr expr::variable(std::string name) {
    return std::make_shared<exprs::variable>(exprs::variable(name));
}
const expr expr::ZERO = expr::number(0.0);
const expr expr::ONE = expr::number(1.0);

// TODO:
//       expr::number, expr::variable, operator==, operator<<,
//       create_expression_tree

expr create_expression_tree(const std::string& expression) {
    std::stringstream ss(expression);
    Tokenizer tokenizer(ss);
    std::vector<Token> ret;
    while (1)
    {
        Token token = tokenizer.next();
        ret.push_back(token);
        if (token.id == TokenId::End){
            break;
        }
    }
}

//OPERATORS AND FUNCS
bool operator==(const expr &a, const expr &b) {
    return a->equals(b->shared_from_this().operator*());
}
std::ostream& operator<<(std::ostream &os, const expr &e) {
    e->write(os,expr::WriteFormat::Infix);
    return os;
}
expr operator+(expr lhs, expr rhs){
    return std::make_shared<exprs::expr_plus>(exprs::expr_plus(lhs,rhs));
}
expr operator-(expr lhs, expr rhs){
    return std::make_shared<exprs::expr_minus>(exprs::expr_minus(lhs,rhs));
}
expr operator*(expr lhs, expr rhs){
    return std::make_shared<exprs::expr_multiply>(exprs::expr_multiply(lhs,rhs));
}
expr operator/(expr lhs, expr rhs){
    return std::make_shared<exprs::expr_divide>(exprs::expr_divide(lhs,rhs));
}
expr pow(expr num, expr exponent){
    return std::make_shared<exprs::expr_pow>(exprs::expr_pow(num,exponent));
}
expr log(expr e){
    return std::make_shared<exprs::expr_log>(exprs::expr_log(e));
}
expr sin(expr e){
    return std::make_shared<exprs::expr_sin>(exprs::expr_sin(e));
}
expr cos(expr e){
    return std::make_shared<exprs::expr_cos>(exprs::expr_cos(e));
}

