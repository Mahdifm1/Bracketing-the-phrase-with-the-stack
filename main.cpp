#include <iostream>
#include "Stack.hpp"
#include "Symbols.hpp"

void bracketsForNegativeSign(Stack &inputStack) {
    std::string inputString = inputStack.stackToString();
    std::string stringReplace;
    Symbols symbols;
    int firstLen = inputString.length();
    int count = 0;
    for (int i = 0; i < inputString.length(); ++i) {
        if (symbols.findSymbolPriority(inputString[i]) != 0) {
            if (inputString[i + 1] == '-') {
                stringReplace = "(-";
                int j, NumberDigits=0;
                for (j = i + 2; (inputString[j] >= 48 && inputString[j] <= 57) || inputString[j] == '.'; ++j) {
                    stringReplace += inputString[j];
                    NumberDigits++;
                }
                stringReplace += ")";

                inputString.replace(j - 2 , NumberDigits + 1, stringReplace);
                std::cout <<inputString<< "\n";
            }
        }
    }
}

int main() {
    std::string input;
    std::cin >> input;

    Stack inputStack;
    inputStack.pushStringToStack(input);

    bracketsForNegativeSign(inputStack);
    return 0;
}
