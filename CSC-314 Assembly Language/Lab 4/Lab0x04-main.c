#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

extern int _sumAndPrintList(int* list, int length);

void error() { printf("Invalid input!\n"); }

int main()
{
    int arraysize = 256;
    int *numbers = malloc(arraysize * sizeof(int));
    int length = 0;

    int count = 0;
    int number = 0;
    // prompt user to enter numbers
    printf("> Enter a number or ctrl + d to finish.\n");
    while (count < 1000) {
        printf("> ");
        int result = scanf("%d", &number);
        if (result == EOF) break;
        else if (result != 1) { error(); exit(1); }
        else if (number == 0) { error(); exit(1); }
        else if (length == arraysize) {
            arraysize *= 2;
            numbers = realloc(numbers, arraysize * sizeof(int));
            if (!numbers) {
                fprintf(stderr, "Memory allocation failed.\n");
                exit(1);
            }
        }
        numbers[length++] = number;
        count++;
    }
    printf("\n");
    printf("The number of times I smacked my head during the making of this lab was %d.\n", _sumAndPrintList(numbers, length));
    return 0;
}