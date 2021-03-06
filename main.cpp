#include <iostream>
#include <map>
#include "Stack.hpp"
#include "Symbols.hpp"

std::string fDeleteBracket(Stack stack) { //delete extra brackets
    std::string S = stack.stackToString();

    std::map<int, bool> pMap;
    for (int i = 0; i < S.size(); i++) {
        std::map<int, bool>::iterator it;
        if (S.at(i) == '(') {
            pMap[i] = true;
        } else if (S.at(i) == ')') {
            it = pMap.end();
            it--;
            if (!(*it).second) {
                pMap.erase(it);
            } else {
                S.erase(S.begin() + i);
                S.erase(S.begin() + (*it).first);
                pMap.erase(it);
                i = i - 2;
            }
        } else {
            if (!pMap.empty()) {
                it = pMap.end();
                it--;
                (*it).second = false;
            }
        }
    }

    int open = 0, close = 0;
    for (int i = 0; i < S.length(); ++i) {
        if (S[i] == '(')
            open++;
        if (S[i] == ')')
            close++;
    }

    return S;
}

void fBracket(std::string &string, int &i) { //put brackets for normal symbols
    Symbols symbols;
    std::string newString, firstNum = "", secNum = "";
    int countNum1 = 0, countNum2 = 0;
    newString = "(";

    if (string[i - 1] == ')') {
        int close = 1, open = 0;
        firstNum += ")";
        countNum1++;
        int j;
        for (j = i - 2; close != open; --j) {
            if (string[j] == '(')
                open++;
            if (string[j] == ')')
                close++;
            firstNum += string[j];
            countNum1++;
        }
        if ((string[j] >= 65 && string[j] <= 90) || (string[j] >= 97 && string[j] <= 122)) {
            for (; (string[j] >= 65 && string[j] <= 90) || (string[j] >= 97 && string[j] <= 122); --j) {
                firstNum += string[j];
                countNum1++;
            }

        }
        if (string[j] == '-' && (string[j - 1] == '(' || symbols.findSymbolPriority(string[j - 1]) != 0)) {
            firstNum += '-';
            countNum1++;
        }

    } else {
        for (int j = i - 1; (string[j] >= 48 && string[j] <= 57) || string[j] == '.'; --j) {
            firstNum += string[j];
            countNum1++;
        }
    }
    std::reverse(firstNum.begin(), firstNum.end());


    if (string[i + 1] == '-') {
        secNum += '-';
        i++;
        countNum2++;
    }
    if ((string[i + 1] >= 65 && string[i + 1] <= 90) || (string[i + 1] >= 97 && string[i + 1] <= 122)) {
        int j = i + 1;
        for (; (string[j] >= 65 && string[j] <= 90) || (string[j] >= 97 && string[j] <= 122); ++j) {
            secNum += string[j];
            countNum2++;
        }

        secNum += "(";

        if (string[j] >= 48 && string[j] <= 57)
            secNum += string[j];
        int close = 0, open = 1;
        for (j++; close != open; ++j) {
            if (string[j] == ')')
                close++;
            if (string[j] == '(')
                open++;

            secNum += string[j];
            countNum2++;

        }

        countNum2 += 1;
    } else if (string[i + 1] == '(') {
        int close = 0, open = 1;
        secNum += "(";
        countNum2++;

        for (int j = i + 2; close != open; ++j) {
            if (string[j] == '(')
                open++;
            if (string[j] == ')')
                close++;

            secNum += string[j];
            countNum2++;
        }

    } else {
        for (int j = i + 1; (string[j] >= 48 && string[j] <= 57) || string[j] == '.'; ++j) {
            secNum += string[j];
            countNum2++;
        }
    }

    string.replace(i - countNum1, countNum1 + countNum2 + 1, "(" + firstNum + string[i] + secNum + ")");

    i += 2;
}

void fPower(std::string &string, int i) { //1^2^3 -> (1^(2^3))
    Symbols symbols;
    int placePowers[64];
    int countPlacePowers = 0;
    for (int j = i + 1; j < string.length(); ++j) {
        if (symbols.findSymbolPriority(string[j]) != 0) {
            if (string[j] == '^')
                placePowers[countPlacePowers++] = j;
            else
                break;
        }
    }

    for (int j = countPlacePowers - 1; j >= 0; --j) {
        fBracket(string, placePowers[j]);
    }
}

void putBracket(Stack &inputStack) { // find middle symbol
    std::string inputString = inputStack.getStack();
    Symbols symbols;

    for (int k = 1; k < 4; ++k) {
        for (int i = 0; i < inputString.length(); ++i) {
            if (symbols.findSymbolPriority(inputString[i]) != 0 && symbols.findSymbolPriority(inputString[i]) == k) {
                if (inputString[i] == '^') {
                    fPower(inputString, i);
                    fBracket(inputString, i);
                } else
                    fBracket(inputString, i);

            }

        }

    }
    Stack newStack;
    newStack.pushStringToStack(inputString);

    inputStack = newStack;
}

Stack bracketsForNegativeSign(Stack inputStack) { //put bracket for negative numbers and functions
    std::string inputString = inputStack.stackToString();
    std::string stringReplace;
    Symbols symbols;
    Stack stack;

    for (int i = 0; i < inputString.length(); ++i) {
        stack.push(inputString[i]);
        int countCloseBracket = i + 3;

        if ((inputString[i] == '(' || symbols.findSymbolPriority(inputString[i]) != 0) && inputString[i + 1] == '-' &&
            inputString[i + 2] == '(') { //(-(...)) || *-(...)
            int close = 0, open = 1;
            int j;
            stack.push('(');
            stack.push('-');
            stack.push('(');
            for (j = i + 3; close != open; ++j) {
                if (inputString[j] == '(')
                    open++;
                if (inputString[j] == ')')
                    close++;

                countCloseBracket++;
            }

            inputString.insert(j, ")");

            i += 2;
        } else if ((inputString[i] == '(' || symbols.findSymbolPriority(inputString[i]) != 0) &&
                   inputString[i + 1] == '-' && inputString[i + 2] != '(') { // (-sin15 + ... || *-15
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
                if (inputString[j] == '(') {
                    int close = 0, open = 1;
                    stack.push('(');

                    for (j++; close != open; ++j) {
                        if (inputString[j] == ')')
                            close++;
                        if (inputString[j] == '(')
                            open++;
                        stack.push(inputString[j]);

                    }
                } else if (inputString[j] == '-') {
                    stack.push('(');
                    stack.push('-');

                    for (j += 1; (inputString[j] >= 48 && inputString[j] <= 57) || inputString[j] == '.'; ++j) {
                        stack.push(inputString[j]);

                    }
                    stack.push(')');
                } else
                    for (; (inputString[j] >= 48 && inputString[j] <= 57) || inputString[j] == '.'; ++j) {
                        stack.push(inputString[j]);
                    }
                i += j - i - 1;
            }
            stack.push(')');


        } else if ((inputString[i] >= 65 && inputString[i] <= 90) ||
                   (inputString[i] >= 97 && inputString[i] <= 122)) { //sin5 || f(-4)
            std::string func, num;
            int j;
            for (j = i; (inputString[j] >= 65 && inputString[j] <= 90) ||
                        (inputString[j] >= 97 && inputString[j] <= 122); ++j) {
                func += inputString[j];
            }
            if (inputString[j] == '-') {
                num = +"(-";
                j++;
                for (; (inputString[j] >= 48 && inputString[j] <= 57) || inputString[j] == '.'; ++j) {
                    num += inputString[j];
                }
                num += ")";
                i += j - i - 1;

                std::string res = func + num;

                stack.pop();
                for (int k = 0; k < res.length(); ++k) {
                    stack.push(res[k]);
                }

            } else if ((inputString[j] >= 48 && inputString[j] <= 57) || inputString[j] == '.') {
                num = +"(";

                for (; (inputString[j] >= 48 && inputString[j] <= 57) || inputString[j] == '.'; ++j) {
                    num += inputString[j];
                }
                num += ")";
                i += j - i - 1;


                std::string res = func + num;

                stack.pop();
                for (int k = 0; k < res.length(); ++k) {
                    stack.push(res[k]);
                }
            }

        }
    }

    inputString = stack.stackToString();
    Stack newStack;
    for (int i = 0; i < inputString.length(); ++i) {
        newStack.push(inputString[i]);
        if (symbols.findSymbolPriority(inputString[i]) != 0 && inputString[i + 1] == '-') {
            newStack.push('(');
            newStack.push('-');
            i++;
            int close = 0, open = 1;
            for (int j = i + 1; close != open; ++j) {
                if (inputString[j] == ')')
                    close++;
                if (inputString[j] == '(')
                    open++;
                newStack.push(inputString[j]);
                i++;
            }
        }
    }

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
            i++;
        }
        if (input[i] == ')' && ((input[i + 1] >= 65 && input[i + 1] <= 90) ||
                                (input[i + 1] >= 97 && input[i + 1] <= 122))) {
            stack.push('*');
            input.insert(i + 1, "*");
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

    }
    return stack;
}

int main() {
    std::string input;
    std::cin >> input;

    Stack inputStack;
    inputStack = fillInTheBlanksByMultiplying(input);

    inputStack = bracketsForNegativeSign(inputStack);

    putBracket(inputStack);

    std::string s = fDeleteBracket(inputStack);


    int c = 0, o = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '(')
            o++;
        if (s[i] == ')')
            c++;
    }

    while (c < o) {
        s += ")";
        c++;
    }

    std::cout << s;

    return 0;
}
