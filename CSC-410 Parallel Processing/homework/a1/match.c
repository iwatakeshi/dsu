#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/*
  Based on naive string matching
  credits: 
    * http://www.personal.kent.edu/~rmuhamma/Algorithms/MyAlgorithms/StringMatch/naiveStringMatch.htm
    * https://en.wikipedia.org/wiki/String_searching_algorithm
*/
void match(char* text, char* pattern, bool matchCase) {
  int n = strlen(text), m = strlen(pattern);
  int index = -1;
  int matches = 0;
  for (int s = 0; s <= n - m; s++) {
    for (int i = 0; i < m; i++) {
      char p = pattern[i], t = text[s + 1];
      printf("pattern[i]: %c, text[s + i]: %c, equality: %d\n", p, t, p == t);
      bool found = matchCase ? p == t : tolower(p) == tolower(t);
      if (found) { 
        matches++; 
        if(index < 0) index = s;
      }
    }
  }
  if (matchCase) {
    printf("Match found at position %d\n", index < 0 ? 0 : index);
    printf("Number of matches found: %d\n", matches);
  } else {
    printf("Match found at position %d (no-case)\n", index < 0 ? 0 : index);
    printf("Number of matches found: %d (no-case)\n", matches);
  }
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    printf("usage: match <text> <pattern>\n");
    return 0;
  }
  match(argv[1], argv[2], false);
  match(argv[1], argv[2], true);
  return 0;
}