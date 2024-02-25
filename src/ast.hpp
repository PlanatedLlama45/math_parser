#pragma once

#include <iostream>
#include <cmath>
#include <map>
#include <regex>
#include <cstring>
#include "string_util.hpp"

namespace MathParser {

extern std::map<std::string, double> constants;
extern std::string nonFunctionChars;
extern std::map<std::string, uint8_t> PEMDAS;
extern std::vector<std::string> binaryOperators;
extern std::vector<std::string> binaryFunctions;
extern std::regex numberRegex;

class Base_AST {
public:
    Base_AST(void);
    ~Base_AST(void);

    virtual double getValue(void);

protected:
    static double applyUnary(std::string fun, double arg);
    static double applyBinary(std::string fun, double arg1, double arg2);

};


class Value_AST : public Base_AST {
public:
    Value_AST(double value);
    ~Value_AST(void);

    double getValue(void) override;

private:
    double value;

};


class Unary_AST : public Base_AST {
public:
    Unary_AST(std::string function, Base_AST *inner);
    ~Unary_AST(void);

    double getValue(void) override;

private:
    std::string function;
    Base_AST *inner;

};


class Binary_AST : public Base_AST {
public:
    Binary_AST(std::string operation, Base_AST *first, Base_AST *second);
    ~Binary_AST(void);

    double getValue(void) override;

private:
    std::string operation;
    Base_AST *first, *second;

};


class Exception : public std::exception {
public:
    Exception(const char *message);
    ~Exception(void);

    inline const char *what(void) const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override { return message; };

private:
    char *message;

};


extern double solveExpression(std::string expr);
extern Base_AST *parseExpression(std::string expr);
extern bool isValidExpression(std::string expr);

inline double deg2rad(double deg) { return deg * M_PI / 180.0; }

inline double fact(double x) { return std::tgamma(x + 1); }

inline double nPr(double n, double r) { return fact(n) / fact(n - r); }
inline double nCr(double n, double r) { return nPr(n, r) / fact(r); }

};
