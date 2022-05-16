#include <iostream>
#include "Stack.hpp"
#include "Symbols.hpp"


bool bracketing(std::string &string, int n) {
    std::string phrase1, phrase2;
    int countReplace = 0;

    if (string[n - 1] >= 48 && string[n - 1] <= 57) {
        phrase1 += ")";
        for (int i = n - 1; string[i] >= 48 && string[i] <= 57 || string[i] == '.'; --i) {
            phrase1 += string[i];
            countReplace++;
        }
        phrase1 += "(";
        std::reverse(phrase1.begin(), phrase1.end());
    } else if (string[n - 1] == ')') {
//        std::cout<<"string "<<string<<"\n";
        bool negativeBracket = false;
        phrase1 += ")";
        int i = n - 2;
        if (string[i] == ')') {
            i--;
//            phrase1 += ")";
        }
//        std::cout<<"VVV   "<<string[i-2]<<string[i-1]<<string[i]<<string[i+1]<<"\n";
        for (; ((string[i] >= 48 && string[i] <= 57) || string[i] == '.') ||
               (string[i] == '-'); --i) {
            phrase1 += string[i];
            countReplace++;
        }
//        std::cout<<" S "<<phrase1<<"\n";
        if (string[i] == '-') {
            string += '-';
            i--;
        }
        if (string[i + 1] == '-')
            i--;
//        std::cout<<"\n, "<<string[i-2]<<string[i-1]<<string[i]<<string[i+1]<<"\n";
        if ((string[i - 1] >= 65 && string[i - 1] <= 90) || (string[i - 1] >= 97 && string[i - 1] <= 122)) {
            phrase1.insert(0, ")");
            negativeBracket = true;
            phrase1 += "(";
//            std::cout << " i " << string[i];

            for (i--; (string[i] >= 65 && string[i] <= 90) || (string[i] >= 97 && string[i] <= 122); --i) {
                phrase1 += string[i];
                countReplace++;
            }
            if (negativeBracket)
                phrase1 += "(";
        } else {
            int open = 0, close = 1;
            for (; open != close; --i) {
                if (string[i] == '(')
                    open++;
                if (string[i] == ')')
                    close++;
                phrase1 += string[i];
                countReplace++;
            }
        }
//        phrase1+="(";
        std::reverse(phrase1.begin(), phrase1.end());
    }
    string.replace(n - phrase1.length(), n - phrase1.length() - 1, phrase1);
    std::cout << "phrase1 " << phrase1 << "\n" << "phrase2 " << string << "   I " << countReplace << "\n\n";
}

void fPower(std::string &string, int &i) {

    std::string newString, firstNum = "", secNum = "";
    int countNum1 = 0, countNum2 = 0;
    Stack newStack;
    newString = "(";
//    std::cout << "!!! " << string << "\n";

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
//        firstNum += "(";
    } else {
        for (int j = i - 1; (string[j] >= 48 && string[j] <= 57) || string[j] == '.'; --j) {
            firstNum += string[j];
            countNum1++;
        }
    }
    std::reverse(firstNum.begin(), firstNum.end());
//    std::cout<<"\nn"<<firstNum<<"\n";

    if ((string[i + 1] >= 65 && string[i + 1] <= 90) || (string[i + 1] >= 97 && string[i + 1] <= 122)) {
        int j = i + 1;
        bool negative = false;
        if (string[j - 1] == '-')
            negative = true;
//        std::cout<<string[j]<<"    !!!!!\n";
        for (; (string[j] >= 65 && string[j] <= 90) || (string[j] >= 97 && string[j] <= 122); ++j) {
            secNum += string[j];
            countNum2++;
        }
//        if (string[j]=='(')


        secNum += "(";

        int close = 0, open = 1;
        for (j++; close != open; ++j) {
            if (string[j] == ')')
                close++;
            if (string[j] == '(')
                open++;

            secNum += string[j];
            countNum2++;

        }
//        std::cout<<"!!!!!!!!!!!!!  "<<string[j]<<"\n";
//        if (negative)
//            j--;
//        for (j++; (string[j] >= 48 && string[j] <= 57) || string[j] == '.'; ++j) {
//            secNum += string[j];
//            countNum2++;
//        }
//        if (string[j]==')')
//        secNum += ")";
        countNum2 += 2;
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
//        secNum += ")";
    } else {
        for (int j = i + 1; (string[j] >= 48 && string[j] <= 57) || string[j] == '.'; ++j) {
            secNum += string[j];
            countNum2++;
        }
    }
//    std::cout << "I " << i << " count1 " << countNum1 << " count2 " << countNum2 << "\n";

    string.replace(i - countNum1, countNum1 + countNum2 + 1, "(" + firstNum + string[i] + secNum + ")");
//    std::cout << "\nNum1 " << firstNum << " num2: " << secNum << "\n" << "!C " << string << "\n";
    i += 2;
//    std::cout<<"\ndone "<<string[i]<<"\n";
}

void fRoot(Stack &stack, int i) {

}

void fMultiplicationDivisionLeftOver(std::string &string, int i) {
    std::string firstNum = "", secNum = "";
    int countNum1 = 0, countNum2 = 0;

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

    }
}

void fSumSubmission(Stack &stack, int i) {

}

void putBracket(Stack &inputStack) {
    std::string inputString = inputStack.getStack();
    Symbols symbols;

    for (int k = 1; k < 4; ++k) {
        for (int i = 0; i < inputString.length(); ++i) {
            if (symbols.findSymbolPriority(inputString[i]) != 0 && symbols.findSymbolPriority(inputString[i]) == k) {
                if (inputString[i] == '^') {
                    fPower(inputString, i);
                }
//                else if (جذر)
//                    fRoot(inputStack,i);
                else if (inputString[i] == '*')
                    fPower(inputString, i);
//                    fMultiplicationDivisionLeftOver(inputString, i);
                else if (inputString[i] == '/')
                    fPower(inputString, i);
//                    fMultiplicationDivisionLeftOver(inputString, i);
                else if (inputString[i] == '%')
                    fPower(inputString, i);
//                    fMultiplicationDivisionLeftOver(inputString, i);
                else if (inputString[i] == '+')
                    fPower(inputString, i);
//                    fSumSubmission(inputStack, i);
                else if (inputString[i] == '-')
                    fPower(inputString, i);
//                    fSumSubmission(inputStack, i);
//                std::cout << "done " << inputString << " K " << k << "\n";
            }


        }
//        std::cout<<" R "<<inputString<<" K "<<k<<"\n";
    }
    std::cout << "res\n" << inputString << "\n";
}

Stack bracketsForNegativeSign(Stack inputStack) {
    std::string inputString = inputStack.stackToString();
    std::string stringReplace;
    Symbols symbols;
    Stack stack;

    for (int i = 0; i < inputString.length(); ++i) {
        stack.push(inputString[i]);
        int closeSymCount = 0;

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
                stack.push(inputString[j]);

//                i++;
            }
            stack.push(')');

            i += j - i - 1;
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
//                    i++;
                    for (j++; close != open; ++j) {
                        if (inputString[j] == ')')
                            close++;
                        if (inputString[j] == '(')
                            open++;
                        stack.push(inputString[j]);
//                        i++;
                    }
                } else if (inputString[j] == '-') {
                    stack.push('(');
                    stack.push('-');
//                    i+=2;
                    for (j += 1; (inputString[j] >= 48 && inputString[j] <= 57) || inputString[j] == '.'; ++j) {
                        stack.push(inputString[j]);
//                        i++;
                    }
                    stack.push(')');
                } else
                    for (; (inputString[j] >= 48 && inputString[j] <= 57) || inputString[j] == '.'; ++j) {
                        stack.push(inputString[j]);
                    }
                i += j - i - 1;
            }
            stack.push(')');

            std::cout << " ET STAK " << stack.getStack() << "\n";

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
//            std::cout << "RES   " << inputString << "\n";

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
//                std::cout << "N\n" << func << num << " i " << i << " \n";

                std::string res = func + num;
//                std::reverse(res.begin(),res.end());
                stack.pop();
                for (int k = 0; k < res.length(); ++k) {
                    stack.push(res[k]);
                }
//                std::cout<<" RES  "<<func<<"\n";
            } else if ((inputString[j] >= 48 && inputString[j] <= 57) || inputString[j] == '.') {
                num = +"(";
//                j++;
                for (; (inputString[j] >= 48 && inputString[j] <= 57) || inputString[j] == '.'; ++j) {
                    num += inputString[j];
                }
                num += ")";
                i += j - i - 1;
//                std::cout << "N\n" << "num " << num << " i " << i << " \n";

                std::string res = func + num;
//                std::reverse(res.begin(),res.end());
                stack.pop();
                for (int k = 0; k < res.length(); ++k) {
                    stack.push(res[k]);
                }
            }
//            std::cout<<" RES \n"<<res<<"\n";
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

    std::cout << "s \n" << newStack.getStack() << "\n";
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

    putBracket(inputStack);

    std::cout << inputStack.stackToString();
    return 0;
}
