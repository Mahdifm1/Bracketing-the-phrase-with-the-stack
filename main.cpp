#include <iostream>
#include "Stack.hpp"
#include "Symbols.hpp"

void bracketsForNegativeSign(Stack &inputStack) {
    std::string inputString = inputStack.stackToString();
    std::string stringReplace;
    Symbols symbols;

    for (int i = 0; i < inputString.length(); ++i) {
        if (inputString[i] == '(' && inputString[i + 1] == '-') { //for (-sin15 + ...
            int countSymbol = 0;
            stringReplace = "(";
            int j;
            for (j = i + 1; countSymbol < 2; ++j) {
                if (symbols.findSymbolPriority(inputString[j]) != 0 || inputString[i] == ')') {
                    countSymbol++;
                    if (countSymbol == 2)
                        break;
                }

                stringReplace += inputString[j];
            }
            stringReplace += ")";


            if (symbols.findSymbolPriority(inputString[j + 1]) == 0) {
                inputString.replace(i + 1, j - i - 1, stringReplace);
                i++;
            }

            std::cout << inputString << "\n";
        } else if (symbols.findSymbolPriority(inputString[i]) != 0) { //for *-15 +...
            if (((inputString[i + 2] >= 65 && inputString[i + 2] <= 90) ||
                 (inputString[i + 2] >= 97 && inputString[i + 2] <= 122)) &&
                inputString[i + 1] == '-') { // for *-sin15 ...
                stringReplace = "(-";
                int j, numberWords = 0, numberDigits = 0;
                for (j = i + 2; j < (inputString[j] >= 65 && inputString[j] <= 90) ||
                                (inputString[j] >= 97 && inputString[j] <= 122); ++j) {
                    stringReplace += inputString[j];
                    numberWords++;
                }
                stringReplace += "(";
                for (; (inputString[j] >= 48 && inputString[j] <= 57) || inputString[j] == '.'; ++j) {
                    stringReplace += inputString[j];
                    numberDigits++;
                }
                stringReplace += "))";

//                std::cout << stringReplace << "\n";

                inputString.replace(i + 1, numberWords + numberDigits + 1, stringReplace);
            } else if (inputString[i + 1] == '-') { //for *-15 + ...
                stringReplace = "(-";
                int j, numberDigits = 0;
                for (j = i + 2; (inputString[j] >= 48 && inputString[j] <= 57) || inputString[j] == '.'; ++j) {
                    stringReplace += inputString[j];
                    numberDigits++;
                }
                stringReplace += ")";

                inputString.replace(i + 1, numberDigits + 1, stringReplace);
//                std::cout << inputString << " J " << j - numberDigits - 1 << " N " << numberDigits << "\n";
            }
        }

    }
    for (int i = 0; i < inputString.length(); ++i) {
        inputStack.push(inputString[i]);
    }
}

void fillInTheBlanksByMultiplying(std::string &input) { //Filling the blanks by multiplying char
    for (int i = 0; i < input.length(); ++i) {
        if (input[i] == '(' && input[i - 1] > 47 && input[i - 1] < 58) {
            input.insert(i, "*");
            i++;
        }
        if (input[i] == ')' && input[i + 1] > 47 && input[i + 1] < 58) {
            input.insert(i + 1, "*");
            i++;
        }
        if (input[i] == ')' && input[i + 1] == '(') {
            input.insert(i + 1, "*");
            i++;
        }
        if (((input[i] > 47 && input[i] < 58) || input[i] == '.') &&
            ((input[i + 1] >= 65 && input[i + 1] <= 90) || (input[i + 1] >= 97 && input[i + 1] <= 122))) {
            input.insert(i + 1, "*");
        }
    }
//    std::cout << input << "  11" << "\n";
}

int main() {
    std::string input;
    std::cin >> input;
    fillInTheBlanksByMultiplying(input);

    Stack inputStack;
    inputStack.pushStringToStack(input);

    bracketsForNegativeSign(inputStack);

    std::cout << inputStack.stackToString();
    return 0;
}
