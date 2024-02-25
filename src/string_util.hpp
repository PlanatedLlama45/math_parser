#pragma once

#include <string>
#include <algorithm>
#include <vector>

namespace MathParser {
namespace StringUtil {

#define contains(container, value) std::find(container.begin(), container.end(), value) != container.end()

extern void removeChar(std::string &str, char ch = ' ');
extern void trimChar(std::string &str, char ch = ' ');
extern void trimChar(std::string &str, std::string charset);
extern std::vector<std::string> splitAt(std::string str, size_t split, bool skip = false);
extern std::vector<std::string> splitAt(std::string str, std::string::iterator split, bool skip = false);
extern std::vector<std::string> splitAt(std::string str, char ch = ' ');
extern std::string getSubString(std::string::iterator left, std::string::iterator right);
extern std::string getSubString(std::string str, size_t left, size_t right);

};
};
