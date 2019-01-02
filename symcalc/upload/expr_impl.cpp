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
        out << "(+ " << expr1 << " " << expr2 << ")" ;
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
       if(two == expr::ZERO){
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
    bool expr_minus::equals(const expr_base &b) const {
        //get the actual expression from shared pointer
        const expr_minus* expr = dynamic_cast<expr_minus const*>(b.shared_from_this().get());
        if (expr1 == expr->expr1 && expr2 == expr->expr2){
            return true;
        }else{
            return false;
        }
    }
    void expr_minus::write(std::ostream &out, expr_base::WriteFormat fmt) const {
        out << "(- " << expr1 << " " << expr2 << ")" ;
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
    //MULTIPLY
    expr_multiply::expr_multiply(const expr & one, const expr &two) {
        expr1 = one;
        expr2 = two;
    }

    double expr_multiply::evaluate(const expr_base::variable_map_t &variables) const {
        return expr1->evaluate(variables) * expr2->evaluate(variables);
    }

    expr expr_multiply::derive(std::string const &variable) const {
//        throw std::logic_error("not implemented yet");
        return std::make_shared<expr_plus>((expr1->derive(variable) * expr2) , (expr1*expr2->derive(variable)));
    }

    expr expr_multiply::simplify() const {
        expr one = expr1->simplify();
        expr two = expr2->simplify();

        if(one == expr::ZERO || two == expr::ZERO){
            return expr::ZERO;
        }
        if (one == expr::ONE){
            return two;
        }
        if (two == expr::ONE){
            return one;
        }

        return std::make_shared<expr_multiply>(one , two);
    }

    void expr_multiply::write(std::ostream &out, WriteFormat fmt) const {
        out << "(" << "* " << expr1 <<" "  << expr2 << ")";
    }

    bool expr_multiply::equals(const expr_base &b) const {
//        throw std::logic_error("not implemented yet");
        const expr_multiply* exprMultiply = dynamic_cast<expr_multiply const*>(b.shared_from_this().get());
        //cast wasnt successful
        if (exprMultiply == nullptr){
            return false;
        }
        return expr1 == exprMultiply->expr1 && expr2 == exprMultiply->expr2;
    }
    //DEVIDE
    expr_divide::expr_divide(const expr & one, const expr &two) {
        expr1 = one;
        expr2 = two;
    }

    double expr_divide::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_divide::derive(std::string const &variable) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_divide::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    void expr_divide::write(std::ostream &out, WriteFormat fmt) const {
        out << "(/ " << expr1 << " " << expr2 << ")";
    }

    bool expr_divide::equals(const expr_base &b) const {
        throw std::logic_error("not implemented yet");
    }
    //POW
    expr_pow::expr_pow(const expr & one, const expr &two) {
        expr1 = one;
        expr2 = two;
    }

    double expr_pow::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_pow::derive(std::string const &variable) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_pow::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    void expr_pow::write(std::ostream &out, WriteFormat fmt) const {
        out << "(^ " << expr1 << " "  << expr2 << ")";
    }

    bool expr_pow::equals(const expr_base &b) const {
        throw std::logic_error("not implemented yet");
    }
    //SIN
    expr_sin::expr_sin(const expr & one) {
        expr1 = one;
    }

    double expr_sin::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_sin::derive(std::string const &variable) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_sin::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    void expr_sin::write(std::ostream &out, WriteFormat fmt) const {
        out << "(sin " << expr1 << ")";
    }

    bool expr_sin::equals(const expr_base &b) const {
        throw std::logic_error("not implemented yet");
    }
    //COS
    expr_cos::expr_cos(const expr & one) {
        expr1 = one;
    }

    double expr_cos::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_cos::derive(std::string const &variable) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_cos::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    void expr_cos::write(std::ostream &out, WriteFormat fmt) const {
        out << "(cos " << expr1 << ")";
    }

    bool expr_cos::equals(const expr_base &b) const {
        throw std::logic_error("not implemented yet");
    }
    //LOG
    expr_log::expr_log(const expr & one) {
        expr1 = one;
    }

    double expr_log::evaluate(const expr_base::variable_map_t &variables) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_log::derive(std::string const &variable) const {
        throw std::logic_error("not implemented yet");
    }

    expr expr_log::simplify() const {
        throw std::logic_error("not implemented yet");
    }

    void expr_log::write(std::ostream &out, WriteFormat fmt) const {
        out << "(log " << expr1 << ")";
    }

    bool expr_log::equals(const expr_base &b) const {
        throw std::logic_error("not implemented yet");
    }
} // namespace exprs
