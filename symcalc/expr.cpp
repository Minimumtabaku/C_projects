#include "expr.hpp"
#include "expr_impl.hpp"
#include <stdexcept>



exprs::variable::variable(std::string in) {var = in;};

expr exprs::variable::derive(std::string const &variable) const {
    if (var == variable){
        return expr::ONE;
    }else{
        return expr::ZERO;
    }
}
bool exprs::variable::equals(const expr_base &b) const {
    if(const variable* v = dynamic_cast<variable const*>(b.shared_from_this().get())) {
        return v->var == var;
    }
    return false;
}
void exprs::variable::write(std::ostream &out, expr_base::WriteFormat fmt) const {
    out << var;
}
//TODO: check this shieeet, this could produce an error
double exprs::variable::evaluate(const expr_base::variable_map_t &variables) const {
    for(auto pair : variables){
        if(pair.first == var){
            return pair.second;
        }
    }
    throw unbound_variable_exception("");
}
expr exprs::variable::simplify() const {
    return shared_from_this();
}

const expr expr::ZERO = expr::number(0.0);
const expr expr::ONE = expr::number(1.0);

// TODO: overloaded operators +, -, *, /, functions pow, log, sin, cos,
//       expr::number, expr::variable, operator==, operator<<,
//       create_expression_tree

expr create_expression_tree(const std::string& expression) {
    // TODO
    throw std::logic_error("not implemented");
}

bool operator==(const expr &a, const expr &b) {
    // TODO
    throw std::logic_error("not implemented");
}

std::ostream& operator<<(std::ostream &os, const expr &e) {
    // TODO
    throw std::logic_error("not implemented");
}
