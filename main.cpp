#include <iostream>
#include <map>
#include "Stack.hpp"
#include "Symbols.hpp"

std::string fDeleteBracket(Stack stack) {
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

void fPower(std::string &string, int &i) {
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
        bool negative = false;
        if (string[j - 1] == '-')
            negative = true;
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
//        if (string[i+2]=='-') {
//            i++;
//            countNum2++;
//        }
        for (int j = i + 2; close != open; ++j) {
            if (string[j] == '(')
                open++;
            if (string[j] == ')')
                close++;

            secNum += string[j];
            countNum2++;
        }
//        countNum2 = secNum.length();

    } else {
        for (int j = i + 1; (string[j] >= 48 && string[j] <= 57) || string[j] == '.'; ++j) {
            secNum += string[j];
            countNum2++;
        }
    }
//std::cout<<"num2  "<<secNum<<"  countNum2  "<<countNum2<<"\n";
//    if (!(firstNum == "" && (secNum[0] == 65 && secNum[0] <= 90) || (secNum[0] >= 97 && secNum[0] <= 122))) {
        string.replace(i - countNum1, countNum1 + countNum2 + 1, "(" + firstNum + string[i] + secNum + ")");
//        std::cout << "\nNum1 " << firstNum << " num2: " << secNum << "\n" << "!C " << string << "\n";
//    }
    i += 2;
}

void putBracket(Stack &inputStack) {
    std::string inputString = inputStack.getStack();
    Symbols symbols;

    for (int k = 1; k < 4; ++k) {
        for (int i = 0; i < inputString.length(); ++i) {
            if (symbols.findSymbolPriority(inputString[i]) != 0 && symbols.findSymbolPriority(inputString[i]) == k) {
//                else if (جذر)
//                    fRoot(inputStack,i);
//                else

                    fPower(inputString, i);

            }

        }

    }
//    std::cout << "res\n" << inputString << "\n";
    Stack newStack;
    newStack.pushStringToStack(inputString);
//    for (int i = 0; i < inputString.length(); ++i) {
//        newStack.push(inputString[i]);
//    }
    inputStack = newStack;
}

Stack bracketsForNegativeSign(Stack inputStack) {
    std::string inputString = inputStack.stackToString();
    std::string stringReplace;
    Symbols symbols;
    Stack stack;

    for (int i = 0; i < inputString.length(); ++i) {
        stack.push(inputString[i]);
        int countCloseBracket = i + 3;

        if ((inputString[i] == '(' || symbols.findSymbolPriority(inputString[i]) != 0) && inputString[i + 1] == '-' &&
            inputString[i + 2] == '(') {
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
                   (inputString[i] >= 97 && inputString[i] <= 122)) {
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

//    std::cout << "s \n" << newStack.getStack() << "\n";
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

    }
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

    putBracket(inputStack);

    std::string s=fDeleteBracket(inputStack);

//    std::cout <<"\nes\n"<< inputStack.stackToString();
//    std::string s = inputStack.stackToString();
    int c = 0, o = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '(')
            o++;
        if (s[i] == ')')
            c++;
    }

    while (c<o) {
        s+=")";
        c++;
    }

    std::cout << s << "\no " << o << " c " << c;

    return 0;
}
