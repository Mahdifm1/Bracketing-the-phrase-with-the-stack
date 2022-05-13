#include <iostream>
#include "Stack.hpp"
#include "Symbols.hpp"

void bracketsForNegativeSign(Stack &inputStack) {
    std::string inputString = inputStack.stackToString();
    std::string stringReplace;
    Symbols symbols;

    for (int i = 0; i < inputString.length(); ++i) {
        if (symbols.findSymbolPriority(inputString[i]) != 0) {
            if (inputString[i + 1] == '-') {
                stringReplace = "(-";
                int j, numberDigits = 0;
                for (j = i + 2; (inputString[j] >= 48 && inputString[j] <= 57) || inputString[j] == '.'; ++j) {
                    stringReplace += inputString[j];
                    numberDigits++;
                }
                stringReplace += ")";

                inputString.replace(j - numberDigits - 1, numberDigits + 1, stringReplace);
//                std::cout << inputString << " J " << j - numberDigits-1 << " N " << numberDigits << "\n";
            }
        }
    }
    for (int i = 0; i < inputString.length(); ++i) {
        inputStack.push(inputString[i]);
    }
}

int main() {
    std::string input;
    std::cin >> input;

    Stack inputStack;
    inputStack.pushStringToStack(input);

    bracketsForNegativeSign(inputStack);

    std::cout<<inputStack.stackToString();
    return 0;
}
