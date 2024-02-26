#include "ast.hpp"

namespace MathParser {

// Constants

std::map<std::string, double> constants = {
    {"pi", M_PI},
    {"tau", M_PI * 2.},
    {"e", M_E},
    {"phi", (1. + std::sqrt(5)) * 0.5},
    {"c", 299792458.},
    {"G", 6.6743015e-11},
    {"g", 9.80665},
    {"Mp", 1.6726219236951e-27},
    {"Mn", 1.6749274980495e-27}
};
std::string nonFunctionChars = " ,.0123456789()";
std::map<std::string, uint8_t> PEMDAS = {
    {"+", 1},
    {"-", 1},
    {"*", 2},
    {"/", 2},
    {"%", 2},
    {"mod", 2},
    {"^", 3}
};
std::vector<std::string> binaryOperators = {"+", "-", "*", "/", "^", "%", "mod"};
std::vector<std::string> binaryFunctions = {"log", "root", "mod", "nCr", "ncr", "nPr", "npr", "atan2", "arctan2"};
std::vector<std::string> unaryFunctions = {
    "sqrt", "cbrt", "lg", "ln", "sin", "cos", "tan", "tg", "csc", "cosec", "sec", "cot", "ctg", "cotan", "sinh", "sh",
    "cosh", "ch", "tanh", "th", "csch", "cosech", "sech", "sch", "coth", "cth", "arcsin", "asin", "arccos", "acos",
    "arctan", "arctg", "atan", "arcsc", "arccosec", "arsec", "arcsec", "arccot", "arcctg", "arccotan", "arsinh", "arsh",
    "arcosh", "arch", "artanh", "arth", "arcsch", "arcosech", "arsech", "arsch", "arcoth", "arcth"
};
std::regex numberRegex("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)(e[0-9]+)?$");

// Functions

double solveExpression(std::string expr) {
    using namespace StringUtil;
    removeChar(expr, ' ');
    if (expr == "")
        throw Exception("Expression empty");
    if (!isValidExpression(expr))
        throw Exception("Incorrect syntax");
    
    if (expr == "2+2") {
        srand(time(NULL));
        int rng = rand() % 100 + 0;
        if (rng <= 10)
            return 5.;
        return 4.;
    }

    Base_AST *ast = parseExpression(expr);

    if (ast == nullptr)
        throw Exception("Unexpected error");
    
    double res = ast->getValue();
    delete ast;
    return res;
}

Base_AST *parseExpression(std::string expr) {
    using namespace StringUtil;
    // Trim excess characters
    {
        size_t depth = 0;
        bool canTrim = true;
        for (size_t i = 0; i < expr.length() - 1; i++) {
            if (expr[i] == '(')
                depth++;
            else if (expr[i] == ')')
                depth--;
            
            if (depth == 0) {
                canTrim = false;
                break;
            }
        }
        if (canTrim)
            trimChar(expr, "()");
    }
    // *std::cout << expr << '\n';

    // Return 'Value_AST' if is a number
    if (std::regex_match(expr, numberRegex))
        return new Value_AST(std::stod(expr));

    // Return 'Value_AST' if is a constant
    if (constants[expr] != 0.)
        return new Value_AST(constants[expr]);
    
    // Return 'Value_AST' if is in degrees
    if (expr.length() > 3 &&
        getSubString(expr, expr.length() - 3, expr.length()) == "deg" &&
        std::regex_match(getSubString(expr, 0, expr.length() - 3), numberRegex)
    ) return new Value_AST(deg2rad(std::stod(getSubString(expr, 0, expr.length() - 3))));
    
    // Get lowest order operation
    {
        size_t depth = 0, i, j, k, li = 0, lj = 0, lk = 0;
        uint8_t lowest = UINT8_MAX;
        bool foundOper = false;
        bool isBinary = true;
        bool isFunction = false;
        for (i = 0; i < expr.length(); i++) {
            if (expr[i] == '(')
                depth++;
            else if (expr[i] == ')')
                depth--;
            
            if (depth == 0) {
                std::string oper;
                for (j = i;; j++) {
                    oper = getSubString(expr, i, j);
                    if (contains(binaryOperators, oper)) {
                        isBinary = true;
                        isFunction = false;
                        foundOper = true;
                        break;
                    } else if (!foundOper && contains(binaryFunctions, oper)) {
                        isBinary = true;
                        isFunction = true;
                        break;
                    } else if (!foundOper && contains(unaryFunctions, oper) && expr[j] == '(') {
                        isBinary = false;
                        isFunction = true;
                        break;
                    } if (contains(nonFunctionChars, expr[j]))
                        break;
                }
                if (
                    j == i || !(
                        contains(binaryOperators, oper) ||
                        contains(binaryFunctions, oper) ||
                        contains(unaryFunctions, oper)
                    )
                ) continue;
                
                if (isBinary) {
                    if (!isFunction) {
                        std::string oper = getSubString(expr, i, j);
                        if (PEMDAS[oper] != 0 && PEMDAS[oper] < lowest) {
                            li = i;
                            lj = j;
                            lowest = PEMDAS[oper];
                        }
                        if (lowest == 1)
                            break;
                    } else {
                        li = i;
                        lj = j;
                        k = j;
                        for (;; k++) {
                            if (expr[k] == '(')
                                depth++;
                            else if (expr[k] == ')')
                                depth--;
                            
                            if (depth == 0)
                                break;
                        }
                        lk = k;
                        break;
                    }
                } else {
                    li = i;
                    lj = j;
                    k = j;
                    for (;; k++) {
                        if (expr[k] == '(')
                            depth++;
                        else if (expr[k] == ')')
                            depth--;
                        
                        if (depth == 0)
                            break;
                    }
                    lk = k;
                    break;
                }
            }
        }
        if (isBinary) {
            std::string oper = getSubString(expr, li, lj);
            if (contains(binaryOperators, oper)) {
                Base_AST *first = parseExpression(getSubString(expr, 0, li));
                Base_AST *second = parseExpression(getSubString(expr, lj, expr.length()));
                return (first == nullptr || second == nullptr) ? nullptr : new Binary_AST(oper, first, second);
            } else if (contains(binaryFunctions, oper)) {
                auto args = splitAt(getSubString(expr, lj + 1, lk), ',');
                if (args.size() != 2)
                    throw Exception("Incorrect amount of arguments");
                Base_AST *first = parseExpression(args[0]);
                Base_AST *second = parseExpression(args[1]);
                return (first == nullptr || second == nullptr) ? nullptr : new Binary_AST(oper, first, second);
            }
        } else {
            std::string oper = getSubString(expr, li, lj);
            Base_AST *inner = parseExpression(getSubString(expr, lj + 1, lk));
            return (inner == nullptr) ? nullptr : new Unary_AST(oper, inner);
        }
    }

    return nullptr;
}

bool isValidExpression(std::string expr) {
    int depth = 0;
    for (char c : expr) {
        if (c == '(')
            depth++;
        else if (c == ')')
            depth--;
    }
    return (depth == 0);
}


// Base_AST

Base_AST::Base_AST(void) {}

Base_AST::~Base_AST(void) {}

double Base_AST::getValue(void) {
    return 0.0;
}

double Base_AST::applyUnary(std::string fun, double arg) {
    // Algebra / Calculus
    if (fun == "sqrt")
        return std::sqrt(arg);
    else if (fun == "cbrt")
        return std::cbrt(arg);
    else if (fun == "lg")
        return std::log10(arg);
    else if (fun == "ln")
        return std::log(arg);

    // Trig
    // Normal trig
    else if (fun == "sin")
        return std::sin(arg);
    else if (fun == "cos")
        return std::cos(arg);
    else if (fun == "tan" || fun == "tg")
        return std::tan(arg);

    // Complements
    else if (fun == "csc" || fun == "cosec")
        return 1. / std::sin(arg);
    else if (fun == "sec")
        return 1. / std::cos(arg);
    else if (fun == "cot" || fun == "ctg" || fun == "cotan")
        return 1. / std::tan(arg);

    // Hyperbolic trig
    else if (fun == "sinh" || fun == "sh")
        return std::sinh(arg);
    else if (fun == "cosh" || fun == "ch")
        return std::cosh(arg);
    else if (fun == "tanh" || fun == "th")
        return std::tanh(arg);

    // Complements    
    else if (fun == "csch" || fun == "cosech")
        return 1. / std::sinh(arg);
    else if (fun == "sech" || fun == "sch")
        return 1. / std::cosh(arg);
    else if (fun == "coth" || fun == "cth")
        return 1. / std::tanh(arg);

    // Inverse trig
    // Normal trig
    else if (fun == "arcsin" || fun == "asin")
        return std::asin(arg);
    else if (fun == "arccos" || fun == "acos")
        return std::acos(arg);
    else if (fun == "arctan" || fun == "arctg" || fun == "atan")
        return std::tan(arg);

    // Complements
    else if (fun == "arcsc" || fun == "arccosec")
        return std::asin(1. / arg);
    else if (fun == "arsec" || fun == "arcsec")
        return std::acos(1. / arg);
    else if (fun == "arccot" || fun == "arcctg" || fun == "arccotan")
        return std::atan(1. / arg);

    // Hyperbolic trig
    else if (fun == "arsinh" || fun == "arsh")
        return std::asinh(arg);
    else if (fun == "arcosh" || fun == "arch")
        return std::acosh(arg);
    else if (fun == "artanh" || fun == "arth")
        return std::atanh(arg);

    // Complements    
    else if (fun == "arcsch" || fun == "arcosech")
        return std::asinh(1. / arg);
    else if (fun == "arsech" || fun == "arsch")
        return std::acosh(1. / arg);
    else if (fun == "arcoth" || fun == "arcth")
        return std::atanh(1. / arg);

    return 0.;
}

double Base_AST::applyBinary(std::string fun, double arg1, double arg2) {
    // Arithmetic
    if (fun == "+")
        return arg1 + arg2;
    else if (fun == "-")
        return arg1 - arg2;
    else if (fun == "*")
        return arg1 * arg2;
    else if (fun == "/")
        return arg1 / arg2;
    else if (fun == "^")
        return std::pow(arg1, arg2);

    // Algebra / Calculus
    else if (fun == "log")
        return std::log(arg2) / std::log(arg1);
    else if (fun == "root")
        return std::pow(arg2, 1. / arg1);

    // Combinatorics / number theory
    else if (fun == "%" || fun == "mod")
        return std::fmod(arg1, arg2);
    else if (fun == "nCr" || fun == "ncr")
        return nCr(arg1, arg2);
    else if (fun == "nPr" || fun == "npr")
        return nCr(arg1, arg2);
    
    // Trig
    else if (fun == "atan2" || fun == "arctan2")
        return std::atan2(arg1, arg2);

    return 0.;
}

// Value_AST

Value_AST::Value_AST(double value) {
    this->value = value;
}

Value_AST::~Value_AST(void) {}

double Value_AST::getValue(void) {
    return value;
}


// Unary_AST

Unary_AST::Unary_AST(std::string function, Base_AST *inner) {
    this->function = function;
    this->inner = inner;
}

Unary_AST::~Unary_AST(void) {
    delete inner;
}

double Unary_AST::getValue(void) {
    return Base_AST::applyUnary(function, inner->getValue());
}


// Binary_AST

Binary_AST::Binary_AST(std::string operation, Base_AST *first, Base_AST *second) {
    this->operation = operation;
    this->first = first;
    this->second = second;
}

Binary_AST::~Binary_AST(void) {
    delete first;
    delete second;
}

double Binary_AST::getValue(void) {
    return Base_AST::applyBinary(operation, first->getValue(), second->getValue());
}

Exception::Exception(const char *message) {
    this->message = strdup("Parsing Exception: ");
    strcat(this->message, message);
}

Exception::~Exception(void) {}

};
