#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int pos = 0;
char line[1000];
int len;

void parseProgram();
void parsePairList();
void parsePair();

char current() { return line[pos]; }
char accept(char expected) {
    if(current() != expected) {
        printf("syntax error: expected '%c' but found '%c'\n", expected, current());
        exit(1);
    }
    return line[pos++];
}

void parseProgram() { parsePairList(); accept('.'); }

void parsePairList() { while(current() == '(' || current() == '{' || current() == '[') { parsePair(); } }
void parsePair() {
    switch (current()) {
        case '(': accept('('); parsePairList(); accept(')'); break;
        case '{': accept('{'); parsePairList(); accept('}'); break;
        case '[': accept('['); parsePairList(); accept(']'); break;
    }
}

/* removes whitespace */
void trimws(char *str) {
    int count = 0;
    for (int i = 0; str[i]; i++) { if (str[i] != ' ') str[count++] = str[i]; }
    str[count] = '\0';
}

int main() {
	fgets( line, 1000, stdin);
	len = strlen(line) - 1;
	line[len] = '\0';
    trimws(line);
    parseProgram();
    printf("Input - OK\n");
	return 0;
}