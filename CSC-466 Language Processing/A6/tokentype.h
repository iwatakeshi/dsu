#ifndef TOKENTYPE_H
#define TOKENTYPE_H

int coercetype(char op, int left, int right) {
    const int INT = 10, FLOAT = 20, OTHER = -1;
    switch(op) {
        case '+':
        case '-':
        case '*': {
            if (left == INT && right == INT) return INT;
            if (left == INT && right == FLOAT) return FLOAT;
            if (left == FLOAT && right == FLOAT) return FLOAT;
            if (left == FLOAT && right == FLOAT) return FLOAT;
        }
        break;
        case '/': return FLOAT;
        default: return OTHER;
    }
}

const char* gettypestr(int type) {
    // INT = 10 FLOAT = 20
    switch(type) {
        case 10: return "INT";
        case 20: return "FLOAT";
        case 30: return "BOOL";
        default: return "OTHER";
    }
}

#endif