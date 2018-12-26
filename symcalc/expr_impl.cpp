#include "expr_impl.hpp"

#include <iostream>
#include <cmath>
#include <limits>

namespace exprs {
    exprs::number::number(double number) {num = number;};

    expr exprs::number::derive(std::string const &variable) const {
        return expr::ZERO;
    }
    bool exprs::number::equals(const expr_base &b) const {
        if(const number* v = dynamic_cast<number const*>(b.shared_from_this().get())) {
            return v->num == num;
        }
        return false;
    }
    void exprs::number::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        out << num;
    }
    double exprs::number::evaluate(const expr_base::variable_map_t &variables) const {
        return num;
    }
    expr exprs::number::simplify() const {
        return shared_from_this();
    }
    //PLUS
    expr_plus::expr_plus(const expr & one, const expr & two) {
        expr1 = one;
        expr2 = two;
    }
    expr expr_plus::derive(std::string const &variable) const {
        return std::make_shared<expr_plus>(expr_plus(expr1->derive(variable), expr2->derive(variable)));
    }
    bool expr_plus::equals(const expr_base &b) const {
        //get the actual expression from shared pointer
        const expr_plus* expr = dynamic_cast<expr_plus const*>(b.shared_from_this().get());
        if (expr1 == expr->expr1 && expr2 == expr->expr2){
            return true;
        }else{
            return false;
        }
    }
    void expr_plus::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        if(fmt == expr_base::WriteFormat::Infix){
            out << "(" << expr1 << " + " << expr2 << ")";
        } else if(fmt == expr_base::WriteFormat::Postfix){
            out << "(";
            out << expr1;
            out << " ";
            out << expr2;
            out << " +)";
        } else {
            out << "(+ " << expr1 << " " << expr2 << ")";
        }
    }
    double expr_plus::evaluate(const expr_base::variable_map_t &variables) const {
        return expr1->evaluate(variables) + expr2->evaluate(variables);
    }
    expr expr_plus::simplify() const {
       expr one = expr1->simplify();
       expr two = expr2->simplify();

       if (one == expr::ZERO){
           return two;
       }
       if(two == expr::ONE){
           return one;
       }
       return std::make_shared<expr_plus>(expr_plus(one,two));
    }
    //MINUS
    expr_minus::expr_minus(const expr &one, const expr &two) {
        expr1 = one;
        expr2 = two;
    }
    expr expr_minus::derive(std::string const &variable) const {
        return std::make_shared<expr_minus>(expr_minus(expr1->derive(variable), expr2->derive(variable)));
    }
    void expr_minus::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        if(fmt == expr_base::WriteFormat::Infix){
            out << "(" << expr1 << " - " << expr2 << ")";
        } else if(fmt == expr_base::WriteFormat::Postfix){
            out << "(";
            out << expr1;
            out << " ";
            out << expr2;
            out << " -)";
        } else {
            out << "(- " << expr1 << " " << expr2 << ")";
        }
    }
    double expr_minus::evaluate(const expr_base::variable_map_t &variables) const {
        return expr1->evaluate(variables) - expr2->evaluate(variables);
    }
    expr expr_minus::simplify() const {
        expr one = expr1->simplify();
        expr two = expr2->simplify();

        if(two == expr::ONE){
            return one;
        }
        return std::make_shared<expr_minus>(expr_minus(one,two));
    }

} // namespace exprs
