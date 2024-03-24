#include <iostream>
#include "math_parser.hpp"

int main(int argc, char **argv) {
    std::cout << "Enter 'exit' to leave or 'clear' to clear" << std::endl;

    while (true) {
        std::string expr;
        std::cout << "Enter expression: ";
        std::getline(std::cin, expr);

        if (expr == "exit")
            break;
        else if (expr == "clear") {
            system("cls");
            std::cout << "Enter 'exit' to leave or 'clear' to clear" << std::endl;
            continue;
        }
        
        try {
            std::cout << MathParser::solveExpression(expr, MathParser::Unit::Degrees) << std::endl;
        } catch (MathParser::Exception &ex) {
            std::cout << ex.what() << std::endl;
        }
    }

    return 0;
}
