#include <algorithm>

class Stack {
private:
    int top{-1};
    char stack[2056];

public:
    bool push(char p) {
        if (top >= (2056 - 1)) {
            std::cout << "Stack Overflow";
            return false;
        } else {
            stack[++top] = p;
            stack[top + 1] = '\0';
            return true;
        }
    }

    char pop() {
        if (top < 0) {
            std::cout << "Stack Underflow";
            return NULL;
        } else {
            char x = stack[top--];
            return x;
        }
    }

    const char *getStack() {
        return stack;
    }

    int getTop() {
        return top;
    }

    void pushStringToStack(std::string string) {
        for (int i = 0; i < string.length(); ++i) {
            push(string[i]);
        }
    }

    char getTopElement() {
        return stack[top];
    }

    int getElementIn(int i) {
        return stack[i];
    }

    std::string stackToString() {
        std::string s;
        for (int i = 0; i < top+1; i) {
            s += pop();
        }
        std::reverse(s.begin(), s.end());
        return s;
    }
};


