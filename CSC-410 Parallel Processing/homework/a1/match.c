#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/*
  skip
  @description - Determines whether the character at the current position should be skipped
  @return bool
*/
bool skip(int position, char * text) {
  int i = 0;
  while (i < position) {
    // We've seen this character
    if (text[i] == text[position]) return true;
    i++;
  }
  return false;
}

/*
  compare
  @description - Determines whether two characters are equal by strictness.
*/
bool compare(char a, char b, bool strict) {
  return strict ? a == b : tolower(a) == tolower(b);
}

/*
  match
  @description - Matches the characters within the two strings. 
  It will return the farthest positinal match as well as number
  of matches found. Note that duplicates are not counted when
  matching characters. 
  To elaborate, a string A with "COOL socks" and another string B 
  with "boks" have a cross product of A x B =
  {
    (C, b), (C, o), (C, k), (C, s),
    (O, b), (O, o), (O, k), (O, s),
    (O, b), (O, o), (O, k), (O, s),
    (L, b), (L, o), (L, k), (L, s),
    (s, b), (s, o), (s, k), (s, s),
    (o, b), (o, o), (o, k), (o, s),
    (c, b), (c, o), (c, k), (c, s),
    (k, b), (k, o), (k, k), (k, s),
    (s, b), (s, o), (s, k), (s, s)
  }

  A relation R exists if x == y when both are case-sensitive and
  (x, y) has not been matched.
  Thus, R = 
  {
    (s, s), (o, o), (k, k)
  }
  |R| = 3

  A relation S exists if x == y when both are case-insensitive and
  (x, y) has not been matched.
  Thus, S =
  {
    (O, o), (s, s), (o, o), (k, k)
  }
  |S| = 4

*/
void match(char* text, char* text2, bool strict) {
  int n = strlen(text), m = strlen(text2);
  int index = -1;
  int matches = 0;
  int i = 0, j;
  while (i < n) {
    j = 0;
    while (j < m) {
      if (compare(text[i], text2[j], strict)) {
        if (text[i] == '\n') break;
        index = j;
        if (skip(i, text)) break;
        // printf("(%c, %c)\n", text[i], text2[j]);
        matches++;
      }
      j++;
    }
    i++;
  }

  if (strict) {
    printf("Positional Match: %d\n", index);
    printf("Matches: %d\n", matches);
  } else {
    printf("Positional Match: %d (no-case)\n", index);
    printf("Matches: %d (no-case)\n", matches);
  }
}

int main(int argc, char* argv[]) {
  const int bufferSize = 1000;
  char text1[bufferSize], text2[bufferSize];

  printf("Enter the first text: \n");
  fgets(text1, bufferSize, stdin);

  printf("Enter the second text: \n");
  fgets(text2, bufferSize, stdin);
  // Since A x B is not commutative, we'll have to standardize
  // the way the input is processed. In this case, if |A| > |B|
  // then A will be first. Otherwise, B is first.
  char* a = strlen(text1) >= strlen(text2) ? text1 : text2;
  char* b = strlen(text1) <= strlen(text2) ? text1 : text2;
  match(a, b, true);
  match(a, b, false);
  return 0;
}
