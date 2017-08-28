#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
/**
  islinefeed
  @description - Determines whether the character is a line feed.
*/
bool islinefeed(char c) {
  if (c == '\n') return true;
  if (c == '\r') return true;
  return false;
}

/**
  compare
  @description - Determines whether two characters are equal by strictness.
*/
bool compare(char a, char b, bool strict) {
  return strict ? a == b : tolower(a) == tolower(b);
}

/**
  match
  @description - Matches the characters within the two strings.
*/
void match(char* a, char* b, int * result, bool strict) {
  int n = strlen(a), m = strlen(b);
  int positions = 0, matches = 0;

  for (int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if (islinefeed(a[i])) break;
      if (islinefeed(b[j])) break;
      if (compare(a[i], b[j], strict)) {
        if (i == j) positions++;
        matches++;
      }
    }
    result[0] = positions;
    result[1] = matches;
  }
}

int main(int argc, char* argv[]) {
  const int bufferSize = 1000;
  char text1[bufferSize], text2[bufferSize];

  printf("Enter the first text: \n");
  fgets(text1, bufferSize, stdin);

  printf("Enter the second text: \n");
  fgets(text2, bufferSize, stdin);

  char* a = strlen(text1) >= strlen(text2) ? text1 : text2;
  char* b = strlen(text1) < strlen(text2) ? text1 : text2;

  int x[2], y[2];

  match(a, b, x, true);
  match(a, b, y, false);

  printf("Position:  case:   %d  nocase:   %d\n", x[0], y[0]);
  printf("Contains:  case:   %d  nocase:   %d\n", x[1], y[1]);

  return 0;
}
