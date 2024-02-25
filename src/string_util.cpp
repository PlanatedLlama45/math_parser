#include "string_util.hpp"

namespace MathParser {
namespace StringUtil {

void removeChar(std::string &str, char ch) {
    for (auto it = str.begin(); it != str.end();) {
        if (*it == ch)
            str.erase(it);
        else
            it++;
    }
}

void trimChar(std::string &str, char ch) {
    while (str.front() == ch && str.back() == ch) {
        str.erase(str.begin());
        str.erase(--str.end());
    }
}

void trimChar(std::string &str, std::string charset) {
    while (
        contains(charset, str.front()) &&
        contains(charset, str.back())
    ) {
        str.erase(str.begin());
        str.erase(--str.end());
    }
}

std::vector<std::string> splitAt(std::string str, size_t split, bool skip) {
    std::vector<std::string> res(2);
    bool next = false;
    for (size_t i = 0; i < str.length(); i++) {
        if (!next) {
            if (i == split) {
                next = true;
                if (skip) continue;
            }
            res[0] += str[i];
        }
        else
            res[1] += str[i];
    }
    return res;
}

std::vector<std::string> splitAt(std::string str, std::string::iterator split, bool skip) {
    std::vector<std::string> res(2);
    bool next = false;
    for (auto it = str.begin(); it != str.end(); it++) {
        if (!next) {
            if (it == split) {
                next = true;
                if (skip) continue;
            }
            res[0] += *it;
        }
        else
            res[1] += *it;
    }
    return res;
}

std::vector<std::string> splitAt(std::string str, char ch) {
    std::vector<std::string> res;
    std::string curr = "";
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == ch) {
            res.push_back(curr);
            curr = "";
            i++;
        }
        curr += str[i];
    }
    res.push_back(curr);
    return res;
}

std::string getSubString(std::string::iterator left, std::string::iterator right) {
    std::string res;
    for (auto it = left; it != right; it++)
        res += *it;
    return res;
}

std::string getSubString(std::string str, size_t left, size_t right) {
    std::string res;
    for (size_t i = left; i < right; i++)
        res += str[i];
    return res;
}

};
};
