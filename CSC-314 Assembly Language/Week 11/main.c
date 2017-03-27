#include <stdio.h>

int max(int x, int y);

void main() {
    int x, y, m;
    printf("please enter two numbers: ");
    scanf("%d %d", &x, &y);

    m = max(x, y);

    printf("The larger number was (drum roll please)...\n %d\n", m);
}