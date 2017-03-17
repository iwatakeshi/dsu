/*

Read in a line of text  & remove trailing \n
  - allow up to 1024 characters to be in string

Write a function for each & return value to main
  - how many characters
  - how many numeric digits
  - how many spaces
  - how many alphanumeric characters (a-zA-Z0-9)
  - how many  #  symbols in the string
  - find the length of the longest sequence
      of @'s in the string

Print results in main, not in the functions

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int scanCharacters(char line[])
{
  // set position
  int pos = 0;
  // set current character
  char cur = line[pos];
  while (cur != '\0')
  {
    // get next character
    cur = line[++pos];
  }
  return pos;
}

int scanNumbericDigits(char line[])
{
  int pos = 0;
  char cur = line[pos];
  int numOfDigits = 0;
  while (cur != '\0')
  {
    // get the number of digits
    switch (cur)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      numOfDigits++;
      break;
    }
    // get next character
    cur = line[++pos];
  }
  return numOfDigits;
}

int scanSpaces(char line[])
{
  int pos = 0;
  char cur = line[pos];
  int numOfSpaces = 0;
  while (cur != '\0')
  {
    if (cur == ' ')
    {
      numOfSpaces++;
    }
    cur = line[++pos];
  }
  return numOfSpaces;
}

int scanAlphaNumericCharacters(char line[])
{
  int pos = 0;
  char cur = line[pos];
  int numOfDigits = 0;
  int numOfAlphas = 0;
  while (cur != '\0')
  {
    // get the number of digits
    switch (tolower(cur))
    {
    case '0': case '1':
    case '2': case '3':
    case '4': case '5':
    case '6': case '7':
    case '8': case '9':
      numOfDigits++;
      break;
    case 'a': case 'b': case 'c': 
    case 'd': case 'e': case 'f':
    case 'g': case 'h': case 'i': 
    case 'j': case 'k': case 'l':
    case 'm': case 'n': case 'o': 
    case 'p': case 'q': case 'r':
    case 's': case 't': case 'u':
    case 'v': case 'w': case 'x':
    case 'y': case 'z':
      numOfAlphas++;
      break;
    }
    // get next character
    cur = line[++pos];
  }
  return numOfDigits + numOfAlphas;
}

int scanHashTag(char line[])
{
  int pos = 0;
  char cur = line[pos];
  int numOfHasTag = 0;
  while (cur != '\0')
  {
    if (cur == '#')
    {
      numOfHasTag++;
    }
    cur = line[++pos];
  }
  return numOfHasTag;
}

int scanAtTag(char line[])
{
  int pos = 0;
  char cur = line[pos];
  int greatestSequence = 0;
  while (cur != '\0')
  {
    int numOfAtTag = 0;
    switch(cur) {
      case '@':
        while(cur == '@') {
          numOfAtTag += 1;
          if (numOfAtTag > greatestSequence) {
            greatestSequence = numOfAtTag;
          }
          cur = line[++pos];
        }
      break;
    }
    cur = line[++pos];
  }
  return greatestSequence;
}

int main()
{
  char line[1024];
  int len;

  printf("Enter a phrase: ");
  fgets(line, 1024, stdin);

  printf("\nInput: %s\n", line);

  // remove trailing newline
  len = strlen(line);
  len--;
  line[len] = '\0';

  printf("Output: \n");
  printf("\t%d : characters\n", scanCharacters(line));
  printf("\t%d  : digits\n", scanNumbericDigits(line));
  printf("\t%d  : spaces\n", scanSpaces(line));
  printf("\t%d  : alpha numeric\n", scanAlphaNumericCharacters(line));
  printf("\t%d  : # symbols\n", scanHashTag(line));
  printf("\t%d  : longest @ sequence\n", scanAtTag(line));
  return 0;
}
