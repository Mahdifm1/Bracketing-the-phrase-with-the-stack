#include <iostream>
#include "Stack.hpp"
#include "Symbols.hpp"

//void putBracket(Stack &inputStack){
//    std::string inputString = inputStack.stackToString();
//
//    for (int k = 0; k < 4; ++k) {
//        for (int i = 0; i < ; ++i) {
//
//        }
//    }
//}

Stack bracketsForNegativeSign(Stack inputStack) {
    std::string inputString = inputStack.stackToString();
    std::string stringReplace;
    Symbols symbols;
    Stack stack;

    for (int i = 0; i < inputString.length(); ++i) {
        stack.push(inputString[i]);
        int closeSymCount = 0;

        if ((inputString[i] == '(' || symbols.findSymbolPriority(inputString[i]) != 0) &&
            inputString[i + 1] == '-' && inputString[i + 2] != '(') { //for (-sin15 + ...
            stack.push('(');
            stack.push('-');

            int j = 0;
            if (inputString[i + 2] >= 48 && inputString[i + 2] <= 57) {
                for (j = i + 2; (inputString[j] >= 48 && inputString[j] <= 57) || inputString[j] == '.'; ++j) {
                    stack.push(inputString[j]);
                }
                i += j - i - 1;
            } else if ((inputString[i + 2] >= 65 && inputString[i + 2] <= 90) ||
                       (inputString[i + 2] >= 97 && inputString[i + 2] <= 122)) {
                for (j = i + 2; (inputString[j] >= 65 && inputString[j] <= 90) ||
                                (inputString[j] >= 97 && inputString[j] <= 122); ++j) {
                    stack.push(inputString[j]);
                }
                for (; (inputString[j] >= 48 && inputString[j] <= 57) || inputString[j] == '.'; ++j) {
                    stack.push(inputString[j]);
                }
                i += j - i - 1;
            }

            stack.push(')');

        } else if ((symbols.findSymbolPriority(inputString[i]) != 0 && inputString[i + 1] == '-' &&
                    inputString[i + 2] == '(')) {

            stack.push('(');
            stack.push('-');
            stack.push('(');
            int open = 1, close = 0;
            int j;
            for (j = i + 3; close != open; ++j) {
                if (inputString[j] == '(')
                    open++;
                if (inputString[j] == ')')
                    close++;
            }
            inputString.insert(j, ")");
//            stack.push(')');
            i += 2;
//            std::cout << "- p " << stack.getStack()<<"\n";
        }
    }
//    std::cout << "s \n" << stack.getStack() << "\n";
    return stack;
}

Stack fillInTheBlanksByMultiplying(std::string input) { //Filling the blanks by multiplying char
    Stack stack;
    for (int i = 0; i < input.length(); ++i) {
        stack.push(input[i]);
        if (input[i] == '(' && input[i - 1] > 47 && input[i - 1] < 58) {
            char c = stack.pop();
            stack.push('*');
            stack.push(c);
            input.insert(i, "*");
            i++;
        }
        if (input[i] == ')' && input[i + 1] > 47 && input[i + 1] < 58) {
            stack.push('*');
            input.insert(i + 1, "*");
//            std::cout<<" i "<<i<<" ";
            i++;
        }
        if (input[i] == ')' && ((input[i + 1] >= 65 && input[i + 1] <= 90) ||
                                (input[i + 1] >= 97 && input[i + 1] <= 122))) {
            stack.push('*');
            input.insert(i + 1, "*");
//            std::cout<<" i "<<i<<" ";
            i++;
        }
        if (input[i] == ')' && input[i + 1] == '(') {
            stack.push('*');
            input.insert(i + 1, "*");
            i++;
        }
        if (((input[i] > 47 && input[i] < 58) || input[i] == '.') &&
            ((input[i + 1] >= 65 && input[i + 1] <= 90) || (input[i + 1] >= 97 && input[i + 1] <= 122))) {
            stack.push('*');
            input.insert(i + 1, "*");
            i++;
        }
//        std::cout<<"S "<<stack.getStack()<<"\n";
    }
    std::cout << "STACK \n" << stack.getStack() << "\n";
    return stack;
//    std::cout << input << "  11" << "\n";
}

int main() {
    std::string input;
    std::cin >> input;

    Stack inputStack;
    inputStack = fillInTheBlanksByMultiplying(input);

//    inputStack.pushStringToStack(input);
    inputStack = bracketsForNegativeSign(inputStack);

    std::cout << inputStack.stackToString();
    return 0;
}
