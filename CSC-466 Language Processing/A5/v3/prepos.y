
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


%token    NUMBER

%%

input
    :  /* empty */
    |  input line
    ;

line
    : '\n'
    |  expression '\n'            {  printf("value = %d\n",$1.ival); 
                                     printf("----------------------\n");
                                  }
    ;

expression
    :
    | expression '+' expression     { $$.ival = $1.ival + $3.ival; }
    | expression '-' expression     { $$.ival = $1.ival - $3.ival; }
    | expression '*' expression     { $$.ival = $1.ival * $3.ival; }
    | expression '/' expression     { $$.ival = $1.ival / $3.ival; }
    | expression '%' expression     { $$.ival = $1.ival % $3.ival; }
    | expression '^' expression     { $$.ival = pow($1.ival, $3.ival); }
    | '(' expression ')'            { $$.ival = $2.ival; }
    | factor                        { $$.ival = $1.ival; }
    ;

factor
    :  NUMBER               { $$.ival = $1.ival; }
    ;

%%


int main ()
{
  yyparse ();
  return 0;
}

void yyerror (char *s)  /* Called by yyparse on error */
{
  printf ("\terror: %s\n", s);
}

