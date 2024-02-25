#include <iostream>
#include "ast.hpp"

int main(int argc, char **argv) {
    std::cout << "Enter 'exit' to leave or 'clear' to clear" << std::endl;

    while (true) {
        std::string expr;
        std::cout << "Enter expression: ";
        std::getline(std::cin, expr);

        if (expr == "exit")
            break;
        else if (expr == "clear") {
            std::cout << "\033[2J\033[H";
            std::cout << "Enter 'exit' to leave or 'clear' to clear" << std::endl;
            continue;
        }
        
        try {
            std::cout << MathParser::solveExpression(expr) << std::endl;
        } catch (MathParser::Exception &ex) {
            std::cout << ex.what() << std::endl;
        }
    }

    return 0;
}
