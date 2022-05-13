class Symbols {  //symbol class
private:
    char priority[7][2];

public:
    Symbols() {
        priority[0][0] = '^';
        priority[0][1] = 1;
        priority[1][0];//       جذر
        priority[1][1] = 1;
        priority[2][0] = '%';
        priority[2][1] = 2;
        priority[3][0] = '*';
        priority[3][1] = 2;
        priority[4][0] = '/';
        priority[4][1] = 2;
        priority[5][0] = '+';
        priority[5][1] = 3;
        priority[6][0] = '-';
        priority[6][1] = 3;
    }

    int findSymbolPriority(char c) {

        for (int i = 0; i < 7; ++i) {
            if (c == priority[i][0])
                return priority[i][1];
        }

        return 0;
    }
};