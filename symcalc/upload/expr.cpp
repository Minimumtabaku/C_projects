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
        default:
            throw "undefined function identifier from calculate func";
    }
}

expr calculate_result_from_queue(std::queue<Token> rpnQueue) {
    int counter = 0;
    expr x, y;
    std::stack<expr> expressions;
    Token symbol;

    if (rpnQueue.empty()){
        throw parse_error("empty input");
    }

    while (1) {
        if(rpnQueue.empty()){
            break;
        }
        symbol = rpnQueue.front();
        rpnQueue.pop();
        // inputs like ""variable, aaa, bleh"
        if (symbol.id == TokenId::Identifier && !symbol.is_function()) {
            expressions.push(expr::variable(symbol.identifier));
        } else if (symbol.id == TokenId::Number ) {
            expressions.push(expr::number(symbol.number));
        } else if(symbol.id == TokenId::Identifier && symbol.is_function()) {
            if (expressions.empty()){
                throw unbound_variable_exception("nothing to calculate");
            }
            y = expressions.top();
            expressions.pop();
            expressions.push(apply_token(symbol,x,y));
        } else{
            if (expressions.size() < 2){
                throw parse_error("not enough operands");
            }
            y = expressions.top();
            expressions.pop();
            x = expressions.top();
            expressions.pop();
            expressions.push(apply_token(symbol,x,y));
        }
    }

    if (expressions.size() >=2){
        expr expr1 = expressions.top();
        expressions.pop();
        expr expr2 = expressions.top();
        expressions.pop();

        const exprs::variable* one = dynamic_cast<exprs::variable const*>(expr1.operator->());
        const exprs::variable* two = dynamic_cast<exprs::variable const*>(expr2.operator->());
        const exprs::number* three = dynamic_cast<exprs::number const*>(expr1.operator->());
        const exprs::number* four = dynamic_cast<exprs::number const*>(expr2.operator->());

        if ( (one && three) || (one && four) || (two && three) || (two && four) ){
            throw unknown_function_exception("dont know the func bro");
        } else{
            expressions.push(expr2);
            expressions.push(expr1);
        }
    }

    if (expressions.size() > 1){
        throw parse_error("too many operands");
    }else{
        return expressions.top();
    }

}


expr create_expression_tree(const std::string &expression) {
    int leftParenCounter = 0;
    bool needsParen = false, needsSomething = false, goniometricFuck = false;
    std::queue<Token> queue;
    std::stack<Token> stack ;

    std::stringstream ss(expression);
    Tokenizer tokenizer(ss);
    while (1) {
        Token token = tokenizer.next();

        if (token.id == TokenId::End) {
            if (needsParen || needsSomething) {
                throw parse_error("only one paren or nothing in between them");
            }
            break;
        } else if (token.id == TokenId::Number) {
            if (goniometricFuck) {
                throw parse_error("goniometric func without parenthesis");
            }
            queue.push(token);
            needsSomething = false;
        } else if (token.id == TokenId::Identifier && !token.is_function()) {
            queue.push(token);
            needsSomething = false;
            if (goniometricFuck) {
                throw parse_error("goniometric func without parenthesis");
            }
            //sin, cos, ....
        } else if (token.is_function()) {
            stack.push(token);
            needsSomething = false;
            goniometricFuck = true;
        } else if (token.id == TokenId::LParen) {
            needsSomething = true;
            needsParen = true;
            goniometricFuck = false;
            leftParenCounter++;
            stack.push(token);
        } else if (token.id == TokenId::RParen) {
            if (leftParenCounter == 0) {
                throw parse_error("right parenthesis before the left one");
            }
            if (needsSomething == true) {
                throw parse_error("needs something in parenthesis");
            }
            while (!stack.empty() && stack.top().id != TokenId::LParen) {
                queue.push(stack.top());
                stack.pop();
            }
            needsParen = false;
            leftParenCounter--;
            //this should get rid of the last thing: LBracket
            if (!stack.empty()) {
                stack.pop();
            }

        }
            //this is basically checking for the operators
        else {
            while (stack.size() > 0 && (stack.top().is_function()
                                        || (stack.top().is_binary_op() &&
                                            stack.top().op_precedence() > token.op_precedence())
                                        || (stack.top().is_binary_op() &&
                                            stack.top().op_precedence() >= token.op_precedence()
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
//        now we have a queue of symbols in RPN, we have to calculate the result and return expression containg other expressions
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

