#include <stdio.h>

void main() {

  char x, y;
  unsigned char a, b;

  x = 1;

  printf("x = 1: 0x%x\n", x);
  printf("x + 126: 0x%x\n", x + 126);

  x = 128;

  printf("x = 128: 0x%x  %d\n", x, x);

  a = 128;

  printf("a = 128: 0x%x   %d\n", a, a);

}
