/**
 * Abstract Expression: Defines the interface for the interpreter, including the interpret method.
 * Terminal Expression: Symbols in the grammar that cannot be further broken down into smaller units.
 * Non-terminal Expression: Complex expressions in the grammar, composed of terminal and other non-terminal expressions.
 * Context: Contains global information outside of the interpreter, which can store intermediate results of the interpreter or be used to pass information to the interpreter.
 * 
 * Practice:
 * Jack is designing a calculator that interprets simple mathematical expressions entered by the user. 
 * Each expression consists of integers, the addition operator +, and the multiplication operator *, with elements separated by spaces. 
 * Please use the Interpreter pattern to help him implement this system.
 */

#include <iostream>
#include <stack>
#include <iterator>
#include <stdexcept>
#include <stack>
#include <sstream>
#include <vector>
#include <regex>
#include <iterator>


class Expression {
public:
    virtual int interpret() = 0;
    virtual ~Expression() = default;
};


// Terminal expression
class NumberExpression : public Expression {
private:
    int _val;

public:
    NumberExpression(int val) : _val(val) {}

    int interpret() override {
        return _val;
    }
};


// Non-terminal expression
class AddExpression : public Expression {
private:
    Expression* _left, * _right;

public:
    AddExpression(Expression* l, Expression* r) : _left(l), _right(r) {}

    int interpret() override {
        return _left->interpret() + _right->interpret();
    }
};


// Non-terminal
class MultiplyExpression : public Expression {
private:
    Expression* _left, * _right;

public:
    MultiplyExpression(Expression* l, Expression* r) : _left(l), _right(r) {}

    int interpret() override {
        return _left->interpret() * _right->interpret();
    }
};


// Non-terminal
class OperatorExpression : public Expression {
private:
    std::string _op;

public:
    OperatorExpression(const std::string& op) : _op(op) {}

    int interpret() override {
        throw std::runtime_error("OperatorExpression does not support interpretation");
    }

    std::string getOp() {
        return _op;
    }
};


int parseExpression(const std::string& expressionStr) {
    std::istringstream iss(expressionStr);
    std::vector<std::string> elements(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
    std::stack<Expression*> stack;

    for (const auto& element : elements) {
        if (std::regex_match(element, std::regex("\\d+"))) {
            stack.push(new NumberExpression(std::stoi(element)));
        } else if (element == "+" || element == "*") {
            stack.push(new OperatorExpression(element));
        } else {
            throw std::invalid_argument("Invalid element in expression: " + element);
        }
    }

    while (stack.size() > 1) {
        Expression* right = stack.top();
        stack.pop();
        Expression* operatorExp = stack.top();
        stack.pop();
        Expression* left = stack.top();
        stack.pop();

        if (auto* opExp = dynamic_cast<OperatorExpression*>(operatorExp)) {
            std::string op = opExp->getOp();
            if (op == "+") {
                stack.push(new AddExpression(left, right));
            } else if (op == "*") {
                stack.push(new MultiplyExpression(left, right));
            }
        } else {
            throw std::invalid_argument("Invalid operator type in expression");
        }
    }

    int result = stack.top()->interpret();
    delete stack.top(); 
    return result;
}

int main() {
    std::vector<std::string> input_lines;
    std::string line;

    while (std::getline(std::cin, line) && !line.empty()) {
        input_lines.push_back(line);
    }

    for (size_t i = 0; i < input_lines.size(); ++i) {
        try {
            int result = parseExpression(input_lines[i]);
            std::cout << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error - " << e.what() << std::endl;
        }
    }

    return 0;
}

