#include "expr_impl.hpp"

#include <iostream>
#include <cmath>
#include <limits>

namespace exprs {



    number::number(double number) {num = number;};

    expr number::derive(std::string const &variable) const {
        return expr::ZERO;
    }
    bool number::equals(const expr_base &b) const {
        if(const number* v = dynamic_cast<number const*>(b.shared_from_this().get())) {
            return v->num == num;
        }
        return false;
    }
    void number::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        out << num;
    }
    double number::evaluate(const expr_base::variable_map_t &variables) const {
        return num;
    }
    expr number::simplify() const {
        return shared_from_this();
    }

    variable::variable(std::string in) {var = in;};

    expr variable::derive(std::string const &variable) const {
        if (var == variable){
            return expr::ONE;
        }else{
            return expr::ZERO;
        }
    }
    bool variable::equals(const expr_base &b) const {
        if(const variable* v = dynamic_cast<variable const*>(b.shared_from_this().get())) {
            return v->var == var;
        }
        return false;
    }
    void variable::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        out << var;
    }
    //TODO: check this shieeet, this could produce an error
    double variable::evaluate(const expr_base::variable_map_t &variables) const {
       for(auto pair : variables){
           if(pair.first == var){
               return pair.second;
           }
       }
       throw unbound_variable_exception("");
    }
    expr variable::simplify() const {
        return shared_from_this();
    }

    expr_plus::expr_plus(const expr & one, const expr & two) {
        expr1 = one;
        expr2 = two;
    }
    expr expr_plus::derive(std::string const &variable) const {
        return std::make_shared<expr_plus>(expr_plus(expr1->derive(variable), expr2->derive(variable)));
    }
    bool expr_plus::equals(const expr_base &b) const {
        if (b.)
    }

} // namespace exprs
