#pragma once

#include <string>
#include <algorithm>
#include <vector>

namespace MathParser {
namespace StringUtil {

#ifndef MATH_PARSER_EN

// Возвращает true если контейнер содержит значение
#define contains(container, value) std::find(container.begin(), container.end(), value) != container.end()


// Удаляет все экземпляры чара в строке на месте
extern void removeChar(std::string &str, char ch = ' ');

// Удаляет все экземпляры чара в конце и начале строки (одинаковое число с обеих строн) на месте
extern void trimChar(std::string &str, char ch = ' ');

// Удаляет все экземпляры чаров из чарсета в конце и начале строки (одинаковое число с обеих строн) на месте
extern void trimChar(std::string &str, std::string charset);


// Разделяет строку по индексу (если skip равен false, то вторая часть включает чар в индексе)
extern std::vector<std::string> splitAt(std::string str, size_t split, bool skip = false);

// Разделяет строку по индексу (если skip равен false, то вторая часть включает чар в индексе)
extern std::vector<std::string> splitAt(std::string str, std::string::iterator split, bool skip = false);

// Разделяет строку в местах чара
extern std::vector<std::string> splitAt(std::string str, char ch = ' ');


// Получить подстроку по итераторам
extern std::string getSubString(std::string::iterator left, std::string::iterator right);

// Получить подстроку по индексам
extern std::string getSubString(std::string str, size_t left, size_t right);

#endif // !MATH_PARSER_EN

#ifdef MATH_PARSER_EN

// Returns true if the container contains the value
#define contains(container, value) std::find(container.begin(), container.end(), value) != container.end()


// Removes all instances of the given character in-place
extern void removeChar(std::string &str, char ch = ' ');

// Removes all instances of the given character from the ends of the string (only equal amounts on every side) in-place
extern void trimChar(std::string &str, char ch = ' ');

// Removes all instances of the given characters from a charset from the ends of the string (only equal amounts on every side) in-place
extern void trimChar(std::string &str, std::string charset);


// Splits the string by index (if skip is false, the second part includes the character at the split index)
extern std::vector<std::string> splitAt(std::string str, size_t split, bool skip = false);

// Splits the string by iterator (if skip is false, the second part includes the character at the split iterator)
extern std::vector<std::string> splitAt(std::string str, std::string::iterator split, bool skip = false);

// Splits the string by a given character
extern std::vector<std::string> splitAt(std::string str, char ch = ' ');


// Get sub-string of a string by iterators
extern std::string getSubString(std::string::iterator left, std::string::iterator right);

// Get sub-string of a string by indicies
extern std::string getSubString(std::string str, size_t left, size_t right);

#endif // MATH_PARSER_EN

};
};
