
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct 
{
 int ival;
 char str[100];
}tstruct ; 

#define YYSTYPE  tstruct 


int yylex();
void yyerror( char *s);



%}


%%

input
    :  /* empty */
    |  input line
    ;

line
    : '\n'
    |  Program '\n' { printf("Input - OK\n"); }
    ;

Program
    : PairList '.'
    ;
PairList
    :
    | PairList Pair
    ;
Pair
    : '(' PairList ')'
    | '{' PairList '}'
    | '[' PairList ']'
    ;

%%


int main ()
{
  yyparse ();
  return 0;
}

void yyerror (char *s)  /* Called by yyparse on error */
{
  printf ("Input - Bad\n");
}

