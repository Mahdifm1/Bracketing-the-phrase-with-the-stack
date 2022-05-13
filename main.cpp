#include <iostream>

int main() {
    std::string input;
    std::cin >> input;

    Stack inputStack;
    inputStack.pushStringToStack(input);

    bracketsForNegativeSign(inputStack);
    return 0;
}
