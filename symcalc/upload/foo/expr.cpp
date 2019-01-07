#include "expr.hpp"
#include "expr_impl.hpp"
#include "tokenizer.hpp"
#include <stdexcept>
#include <sstream>
#include <stack>
#include <queue>
#include <iostream>


expr expr::number(double n) {
    return std::make_shared<exprs::number>(exprs::number(n));
}

expr expr::variable(std::string name) {
    return std::make_shared<exprs::variable>(exprs::variable(name));
}

const expr expr::ZERO = expr::number(0.0);
const expr expr::ONE = expr::number(1.0);

expr check_id(Token token) {
    if (token.id == TokenId::Number) {
        return expr::number(token.number);
    } else {
        return expr::variable(token.identifier);
    }
}

expr apply_token(Token token, expr x, expr y) {
    switch (token.id) {
        case TokenId::Plus:
            return (x + y);
        case TokenId::Minus:
            return (x - y);
        case TokenId::Divide:
            return (x / y);
        case TokenId::Multiply:
            return (x * y);
        case TokenId::Power:
            return (pow(x, y));
        case TokenId::Identifier:
            if (token.identifier.compare("cos") == 0) {
                return cos(y);
            } else if (token.identifier.compare("sin") == 0) {
                return sin(y);
            } else if (token.identifier.compare("log") == 0) {
                return log(y);
            } else {
                throw "undefined function identifier from calculate func";
            }

    }
}

expr calculate_result_from_queue(std::queue<Token> rpnQueue) {
    int counter = 0;
    expr x, y;
    std::stack<Token> symbols;
    std::stack<expr> expressions;
    Token symbol;

    while (1) {

        if (rpnQueue.empty()) {
            while (!symbols.empty()) {
                if (symbols.top().id == TokenId::Number) {
                    expressions.push(expr::number(symbols.top().number));
                    symbols.pop();
                } else {
                    expressions.push(expr::variable(symbols.top().identifier));
                    symbols.pop();
                }
            }
            break;
        }

        symbol = rpnQueue.front();
        rpnQueue.pop();
        // inputs like ""variable, aaa, bleh"
        if (!symbol.is_function() && symbol.id == TokenId::Identifier) {
            symbols.push(symbol);
            counter++;
        } else if (symbol.id != TokenId::Number || symbol.is_function()) {
            // cos, sin, log
            if (symbol.is_function()) {
                if (expressions.size() == 0) {
                    y = check_id(symbols.top());
                    symbols.pop();
                    expressions.push(apply_token(symbol, x, y));
                } else if (expressions.size() > 0) {
                    y = expressions.top();
                    expressions.pop();
                    expressions.push(apply_token(symbol, x, y));
                }
            } else if (expressions.size() == 0) {
                y = check_id(symbols.top());
                symbols.pop();
                x = check_id(symbols.top());
                symbols.pop();
                expressions.push(apply_token(symbol, x, y));
                counter = 0;
            } else if (symbols.size() <= 2 && expressions.size() == 1 && (counter % 2 != 0 || counter == 0)) {
                if (!rpnQueue.empty() && counter == 1){
                    y = check_id(symbols.top());
                    symbols.pop();
                    x = expressions.top();
                    expressions.pop();
                    expressions.push(apply_token(symbol, x, y));
                    counter--;
                }else if(counter == 1 && rpnQueue.empty() && symbol.id != TokenId::Plus){
                    y = check_id(symbols.top());
                    symbols.pop();
                    x = expressions.top();
                    expressions.pop();
                    expressions.push(apply_token(symbol, x, y));
                    counter--;
                }
                else {
                    x = check_id(symbols.top());
                    symbols.pop();
                    y = expressions.top();
                    expressions.pop();
                    expressions.push(apply_token(symbol, x, y));
                    counter--;
                }
                    //expressions.size() == 0
                } else if (symbols.size() >= 2 && counter % 2 == 0) {
                    y = check_id(symbols.top());
                    symbols.pop();
                    x = check_id(symbols.top());
                    symbols.pop();
                    expressions.push(apply_token(symbol, x, y));
                    counter = 0;
                } else if (symbols.size() <= 2 && expressions.size() == 1 &&
                           (symbol.id == TokenId::Multiply || symbol.id == TokenId::Divide ||
                            symbol.id == TokenId::Power)) {
                    y = check_id(symbols.top());
                    symbols.pop();
                    x = expressions.top();
                    expressions.pop();
                    expressions.push(apply_token(symbol, x, y));
                    counter--;
                } else if (symbols.size() < 2 && expressions.size() >= 2) {
                    y = expressions.top();
                    expressions.pop();
                    x = expressions.top();
                    expressions.pop();
                    //TODO: opacne x a y
                    expressions.push(apply_token(symbol, x, y));
                    counter--;
                } else if (symbols.size() != 2 && expressions.size() >= 1) {
                    if (rpnQueue.empty() && counter %2 == 0){
                        x = check_id(symbols.top());
                        symbols.pop();
                        y = expressions.top();
                        expressions.pop();
                        expressions.push(apply_token(symbol, x, y));
                        counter--;
                    }else{
                        y = check_id(symbols.top());
                        symbols.pop();
                        x = expressions.top();
                        expressions.pop();
                        expressions.push(apply_token(symbol, x, y));
                        counter--;
                    }

                } else {
                    throw "error in calculate func";
                }

            } else {
                symbols.push(symbol);
                counter++;
                //item was already popped at the beginning
            }
        }
        return expressions.top();
    }


    expr create_expression_tree(const std::string &expression) {
        std::queue<Token> queue;
        std::stack<Token> stack;

        std::stringstream ss(expression);
        Tokenizer tokenizer(ss);
        while (1) {
            Token token = tokenizer.next();

            if (token.id == TokenId::End) {
                break;
            } else if (token.id == TokenId::Number) {
                queue.push(token);
            } else if (token.id == TokenId::Identifier && !token.is_function()) {
                queue.push(token);
            }else if (token.is_function()) {
                stack.push(token);
            } else if (token.id == TokenId::LParen) {
                stack.push(token);
            } else if (token.id == TokenId::RParen) {
                while (stack.top().id != TokenId::LParen) {
                    queue.push(stack.top());
                    stack.pop();
                }
                //this should get rid of the last thing: LBracket
                stack.pop();
            }
                //this is basically checking for the operators
            else {
                while (stack.size() > 0 && (stack.top().is_function()
                || (stack.top().is_binary_op() && stack.top().op_precedence() > token.op_precedence())
                || (stack.top().is_binary_op() && stack.top().op_precedence() >= token.op_precedence()
                && stack.top().associativity() == Associativity::Left))
                && stack.top().id != TokenId::LParen) {
                    queue.push(stack.top());
                    stack.pop();
                }
                stack.push(token);
            }
        }
        //push the rest of the operands into the queue
        while (!stack.empty()) {
            queue.push(stack.top());
            stack.pop();
        }
        //now we have a queue of symbols in RPN, we have to calculate the result and return expression containg other expressions
//    std::cout << "printing content of queue" ;
//    while(!queue.empty()){
//        std::cout << ";;;" << queue.front();
//        queue.pop();
//    }
//    std::cout << std::endl;

        return calculate_result_from_queue(queue);
    }

//OPERATORS AND FUNCS
    bool operator==(const expr &a, const expr &b) {
        return a->equals(b->shared_from_this().operator*());
    }

    std::ostream &operator<<(std::ostream &os, const expr &e) {
        e->write(os, expr::WriteFormat::Infix);
        return os;
    }

    expr operator+(expr lhs, expr rhs) {
        return std::make_shared<exprs::expr_plus>(exprs::expr_plus(lhs, rhs));
    }

    expr operator-(expr lhs, expr rhs) {
        return std::make_shared<exprs::expr_minus>(exprs::expr_minus(lhs, rhs));
    }

    expr operator*(expr lhs, expr rhs) {
        return std::make_shared<exprs::expr_multiply>(exprs::expr_multiply(lhs, rhs));
    }

    expr operator/(expr lhs, expr rhs) {
        return std::make_shared<exprs::expr_divide>(exprs::expr_divide(lhs, rhs));
    }

    expr pow(expr num, expr exponent) {
        return std::make_shared<exprs::expr_pow>(exprs::expr_pow(num, exponent));
    }

    expr log(expr e) {
        return std::make_shared<exprs::expr_log>(exprs::expr_log(e));
    }

    expr sin(expr e) {
        return std::make_shared<exprs::expr_sin>(exprs::expr_sin(e));
    }

    expr cos(expr e) {
        return std::make_shared<exprs::expr_cos>(exprs::expr_cos(e));
    }

