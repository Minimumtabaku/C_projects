#pragma once

#include "expr.hpp"
#include <iosfwd>

namespace exprs {
    class number : public expr_base {
        friend class expr;

    public:
        explicit number(double);

    private:
        double evaluate(const variable_map_t &variables) const override;

        expr derive(std::string const &variable) const override;

        expr simplify() const override;

        void write(std::ostream &out, WriteFormat fmt) const override;

        bool equals(const expr_base &b) const override;

        double num;
    };

    class variable : public expr_base {
        friend class expr;

    public:
        std::string var;

        explicit variable(std::string);

        double evaluate(const variable_map_t &variables) const override;

        expr derive(std::string const &variable) const override;

        expr simplify() const override;

    private:
        bool equals(const expr_base &b) const override;

    private:
        void write(std::ostream &out, WriteFormat fmt) const override;

    };


    class expr_plus : public expr_base {
        friend class expr;
    public:
        expr_plus(const expr &, const expr &);

    private:
        expr expr1, expr2;

        void write(std::ostream &out, WriteFormat fmt) const override;

        bool equals(const expr_base &b) const override;

        double evaluate(const variable_map_t &variables) const override;

        expr derive(std::string const &variable) const override;

        expr simplify() const override;
    };

    class expr_minus : public expr_base {
        friend class expr;

    public:
        expr_minus(const expr &, const expr &);

    private:
        expr expr1, expr2;

        double evaluate(const variable_map_t &variables) const override;

        expr derive(std::string const &variable) const override;

        expr simplify() const override;

        void write(std::ostream &out, WriteFormat fmt) const override;

        bool equals(const expr_base &b) const override;
    };

    class expr_multiply : public expr_base {
        friend class expr;

    public:
        expr_multiply(const expr &, const expr &);

    private:
        double evaluate(const variable_map_t &variables) const override;

        expr derive(std::string const &variable) const override;

        expr simplify() const override;

        void write(std::ostream &out, WriteFormat fmt) const override;

        bool equals(const expr_base &b) const override;

        expr expr1, expr2;
    };

    class expr_divide : public expr_base {
        friend class expr;

    public:
        expr_divide(const expr &, const expr &);

    private:
        double evaluate(const variable_map_t &variables) const override;

        expr derive(std::string const &variable) const override;

        expr simplify() const override;

        void write(std::ostream &out, WriteFormat fmt) const override;

        bool equals(const expr_base &b) const override;

        expr expr1, expr2;
    };

    class expr_pow : public expr_base {
        friend class expr;

    public:
        expr_pow(const expr &, const expr &);

    private:

        double evaluate(const variable_map_t &variables) const override;

        expr derive(std::string const &variable) const override;

        expr simplify() const override;

        void write(std::ostream &out, WriteFormat fmt) const override;

        bool equals(const expr_base &b) const override;

        expr expr1, expr2;
    };

    class expr_sin : public expr_base {
        friend class expr;

    public:
        expr_sin(const expr &);

    private:
        double evaluate(const variable_map_t &variables) const override;

        expr derive(std::string const &variable) const override;

        expr simplify() const override;

        void write(std::ostream &out, WriteFormat fmt) const override;

        bool equals(const expr_base &b) const override;

        expr expr1;
    };

    class expr_cos : public expr_base {
        friend class expr;

    public:
        expr_cos(const expr &);

    private:
        double evaluate(const variable_map_t &variables) const override;

        expr derive(std::string const &variable) const override;

        expr simplify() const override;

        void write(std::ostream &out, WriteFormat fmt) const override;

        bool equals(const expr_base &b) const override;

        expr expr1;
    };

    class expr_log : public expr_base {
        friend class expr;

    public:
        expr_log(const expr &);

    private:
        double evaluate(const variable_map_t &variables) const override;

        expr derive(std::string const &variable) const override;

        expr simplify() const override;

        void write(std::ostream &out, WriteFormat fmt) const override;

        bool equals(const expr_base &b) const override;

        expr expr1;
    };
}
