#pragma once

#include <iostream>
#include <cmath>
#include <map>
#include <regex>
#include <cstring>
#include "string_util.hpp"

namespace MathParser {

#ifndef MATH_PARSER_EN

// Мап констант
extern std::map<std::string, double> constants;
// Список чаров которые нельзя использовать в названиях функций
extern std::string nonFunctionChars;
// Мап с порядком операций
extern std::map<std::string, uint8_t> PEMDAS;
// Список унарных функций
extern std::vector<std::string> unaryFunctions;
// Список бинарных операторов
extern std::vector<std::string> binaryOperators;
// Список бинарных функций
extern std::vector<std::string> binaryFunctions;
// Регекс для определения является ли строка числом
extern std::regex numberRegex;

/*
Родительский класс для Абстрактного Синтаксического Дерева (АСД)
*/
class Base_AST {
public:
    Base_AST(void);
    ~Base_AST(void);

    // Находит значение Абстрактного Синтаксического Дерева (АСД)
    virtual double getValue(void);

protected:
    // Найти значение унарной функции по имени
    static double applyUnary(std::string fun, double arg);
    // Найти значение бинарной функции по имени
    static double applyBinary(std::string fun, double arg1, double arg2);

};


/*
Узел Абстрактного Синтаксического Дерева (АСД) для хранения значений
*/
class Value_AST : public Base_AST {
public:
    Value_AST(double value);
    ~Value_AST(void);

    // Находит значение Абстрактного Синтаксического Дерева (АСД)
    double getValue(void) override;

private:
    double value;

};


/*
Узел Абстрактного Синтаксического Дерева (АСД) для хранения унарных функций (функций с одним параметром)
*/
class Unary_AST : public Base_AST {
public:
    Unary_AST(std::string function, Base_AST *inner);
    ~Unary_AST(void);

    // Находит значение Абстрактного Синтаксического Дерева (АСД)
    double getValue(void) override;

private:
    std::string function;
    Base_AST *inner;

};


/*
Узел Абстрактного Синтаксического Дерева (АСД) для хранения бинарных функций/операторов (функций с двумя параметрами)
*/
class Binary_AST : public Base_AST {
public:
    Binary_AST(std::string operation, Base_AST *first, Base_AST *second);
    ~Binary_AST(void);

    // Находит значение Абстрактного Синтаксического Дерева (АСД)
    double getValue(void) override;

private:
    std::string operation;
    Base_AST *first, *second;

};

/*
Класс исключений парсинга

Пробрасываются в функциях 'MathParser::solveExpression' и 'MathParser::parseExpression'
*/
class Exception : public std::exception {
public:
    Exception(const char *message);
    ~Exception(void);

    // Возвращает сообщение исключения
    inline const char *what(void) const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override { return message; };

private:
    char *message;

};


// Находит значение выражение
extern double solveExpression(std::string expr);

// Парсит выражение и возвращает АСД
extern Base_AST *parseExpression(std::string expr);

// Проверяет действительно ли выражение (пока что проверяет только скобки)
extern bool isValidExpression(std::string expr);


// Переводит градусы в радианы
inline double deg2rad(double deg) { return deg * M_PI / 180.0; }

// Возвращает факториал действительного числа
inline double fact(double x) { return std::tgamma(x + 1); }


// Возвращает nPr
inline double nPr(double n, double r) { return fact(n) / fact(n - r); }

// Возвращает nCr
inline double nCr(double n, double r) { return nPr(n, r) / fact(r); }

#endif // !MATH_PARSER_EN

#ifdef MATH_PARSER_EN

// A map of constants
extern std::map<std::string, double> constants;
// A list for characters which cannot be used in a function name
extern std::string nonFunctionChars;
// A map with the order of operations (PEMDAS/BOMDAS)
extern std::map<std::string, uint8_t> PEMDAS;
// A list of unary functions
extern std::vector<std::string> unaryFunctions;
// A list of binary operators
extern std::vector<std::string> binaryOperators;
// A list of binary functions
extern std::vector<std::string> binaryFunctions;
// Regex for determining if a string is a number
extern std::regex numberRegex;

/*
Abstract Syntax Tree (AST) parent class
*/
class Base_AST {
public:
    Base_AST(void);
    ~Base_AST(void);

    // Evaluates the Abstract Syntax Tree (AST)
    virtual double getValue(void);

protected:
    // Evaluate a unary function by name
    static double applyUnary(std::string fun, double arg);
    // Evaluate a binary function by name
    static double applyBinary(std::string fun, double arg1, double arg2);

};


/*
Abstract Syntax Tree (AST) node class for storing values
*/
class Value_AST : public Base_AST {
public:
    Value_AST(double value);
    ~Value_AST(void);

    // Evaluates the Abstract Syntax Tree (AST)
    double getValue(void) override;

private:
    double value;

};


/*
Abstract Syntax Tree (AST) node class for storing unary functions (functions with one parameter)
*/
class Unary_AST : public Base_AST {
public:
    Unary_AST(std::string function, Base_AST *inner);
    ~Unary_AST(void);

    // Evaluates the Abstract Syntax Tree (AST)
    double getValue(void) override;

private:
    std::string function;
    Base_AST *inner;

};


/*
Abstract Syntax Tree (AST) node class for storing binary functions/operations (functions with two parameters)
*/
class Binary_AST : public Base_AST {
public:
    Binary_AST(std::string operation, Base_AST *first, Base_AST *second);
    ~Binary_AST(void);

    // Evaluates the Abstract Syntax Tree (AST)
    double getValue(void) override;

private:
    std::string operation;
    Base_AST *first, *second;

};

/*
Parsing Exception class

Are thrown in 'MathParser::solveExpression' and 'MathParser::parseExpression' functions
*/
class Exception : public std::exception {
public:
    Exception(const char *message);
    ~Exception(void);

    // Returns the exception message
    inline const char *what(void) const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override { return message; };

private:
    char *message;

};


// Evaluates the expression
extern double solveExpression(std::string expr);

// Parses the expression and returns an AST
extern Base_AST *parseExpression(std::string expr);

// Checks if an expression is valid (for now only checks parenthesis)
extern bool isValidExpression(std::string expr);


// Converts degrees to radians
inline double deg2rad(double deg) { return deg * M_PI / 180.0; }

// Returns a factorial of a double
inline double fact(double x) { return std::tgamma(x + 1); }


// Returns the nPr
inline double nPr(double n, double r) { return fact(n) / fact(n - r); }

// Returns the nCr
inline double nCr(double n, double r) { return nPr(n, r) / fact(r); }

#endif // MATH_PARSER_EN

};
