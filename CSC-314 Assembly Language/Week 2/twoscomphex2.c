#include <stdio.h>
#include <limits.h>

void main () {

  int x = INT_MAX, i = 0;
  unsigned int a = INT_MAX;
  printf("INT_MAX = %d hex: 0x%08x\n", INT_MIN, INT_MIN);
  printf("INT_MAX = %d hex: 0x%08x\n", INT_MAX, INT_MAX);
  printf("INT_MAX + 1 = %d hex: 0x%08x\n\n", INT_MAX + 1, INT_MAX + 1);

  // numbers near and "above" INT_MAX for **signed** int (rollover)
  for(i = -5; i <= 5; i++) {
	   printf("x = %d in hex: 0x%08x\n", x + i, x + i);
  }

  printf("\n\n----------------------------------------\n\n");

  // numbers near and "above" INT_MAX (signed max int), as ** unsigned** int (no rollover
  for(i = -5; i <= 5; i++) {
	   printf("a = %u in hex: 0x%08x\n", a + i, a + i);
  }

  printf("\n\n----------------------------------------\n\n");

  // nubers near and "above" UINT_MAX (signed max int), **unsigned** int (no rollover)
  a = UINT_MAX;
  for(i = -5; i <= 5; i++) {
	   printf("a = %u in hex: 0x%08x\n", a + i, a + i);
  }

  printf("\n\n----------------------------------------\n\n");

  // numbers near signed 0 integer
  for(i = -5; i <= 5; i++) {
	   printf("x = %d in hex: 0x%08x\n", i, i);
  }

}
