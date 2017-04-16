#ifndef COLORS_H
#define COLORS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* http://stackoverflow.com/a/3219471 */
static const char * GREEN = "\033[1;32m";
static const char * YELLOW = "\033[1;33m";
static const char * BLUE = "\033[1;34m";
static const char * RED = "\033[0;31m";
static const char * MAGENTA = "\033[0;35m";
static const char * CYAN = "\033[0;36m";
static const char * RESET = "\033[0m";

char *red(char * word) {
    char buffer[1000];
    snprintf(buffer, sizeof buffer, "%s%s%s", RED, word, RESET);
    return strcpy((char *)malloc(strlen(buffer) + 1), buffer);
}

char *green(char * word) {
    char buffer[1000];
    snprintf(buffer, sizeof buffer, "%s%s%s", GREEN, word, RESET);
    return strcpy((char *)malloc(strlen(buffer) + 1), buffer);
}

char *yellow(char * word) {
    char buffer[1000];
    snprintf(buffer, sizeof buffer, "%s%s%s", YELLOW, word, RESET);
    return strcpy((char *)malloc(strlen(buffer) + 1), buffer);
}

char *blue(char * word) {
    char buffer[1000];
    snprintf(buffer, sizeof buffer, "%s%s%s", BLUE, word, RESET);
    return strcpy((char *)malloc(strlen(buffer) + 1), buffer);
}

char *magenta(char * word) {
    char buffer[1000];
    snprintf(buffer, sizeof buffer, "%s%s%s", MAGENTA, word, RESET);
    return strcpy((char *)malloc(strlen(buffer) + 1), buffer);
}

char *cyan(char * word) {
    char buffer[1000];
    snprintf(buffer, sizeof buffer, "%s%s%s", CYAN, word, RESET);
    return strcpy((char *)malloc(strlen(buffer) + 1), buffer);
}

#endif