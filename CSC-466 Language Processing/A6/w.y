
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokentype.h"

typedef struct 
{
 char lexeme[25];
 int value;
 int tokentype;
 char tokentypestr[25];
}tstruct ; 

#define YYSTYPE  tstruct  


int yylex();
void yyerror( char *s );


#include "symtab.c"

#define TypeInt 10
#define TypeFloat 20
#define TypeBool 30

%}

%token TStart  
%token TFinish   
%token TBegin  
%token TEnd  
%token TIntLiteral  
%token TFloatLiteral  
%token TBoolLiteral  
%token TPrint  
%token TPrintLn  
%token TIf  
%token TWhile  
%token TLessThan  
%token TGreaterThan  
%token TEqual  
%token TFalse  
%token TTrue  
%token TAssign  
%token TStringLiteral  
%token TIdentifier

%%

p : prog ;

prog : TStart  TFinish
 |  TStart Declaration Statement TFinish  {printf("Prog\n");}
 ;

Declaration : SingleDeclaration { printf("Declaration\n"); }
            | Declaration SingleDeclaration    { printf("DeclarationList\n"); }
            ;

SingleDeclaration : TIdentifier SingleDeclarationTail {
                                                        addtab($1.lexeme);
                                                        printf("lexeme %s\n", $1.lexeme);
                                                        addtype($1.lexeme, $2.tokentype);
                                                      }
                  ;

SingleDeclarationTail : ',' TIdentifier SingleDeclarationTail {
                                                                addtab($2.lexeme);
                                                                addtype($2.lexeme, $3.tokentype);
                                                                $$.tokentype = $3.tokentype;
                                                              }
                      |  ':' Type ';'                         { $$.tokentype = $2.tokentype; }
                      ;

Type: TIntLiteral { $$.tokentype = TypeInt; } | TFloatLiteral { $$.tokentype = TypeFloat; } | TBoolLiteral { $$.tokentype = TypeBool; } ;

Statement : SingleStatement { printf("Statement\n"); }
          | Statement SingleStatement { printf("StatementList\n"); }

SingleStatement : TPrint TStringLiteral ';' { printf("print lit\n"); }
                | TPrintLn TIdentifier ';'  { printf("print id\n");
                                              if ( intab($2.lexeme) )
                                                printf("%s is declared %d\n", $2.lexeme, @2.first_line);
                                              else
                                                printf("UNDECLARED:: %s \n", $2.lexeme);
                                            }       
                |  TPrintLn ';'
                |  TIdentifier TAssign Expression ';'  
                            {
                              printf("assign\n");
                              if ( intab($1.lexeme) )
                                printf("%s is declared\n", $1.lexeme);
                              else
                                printf("UNDECLARED:: %s \n", $1.lexeme);

                              $1.tokentype = gettype($1.lexeme);
                              if ($1.tokentype > 0 ) {
                                // If the types are the same or the left is FLOAT and the right is INT
                                // then we are good to go, otherwise we should report the issue.
                                if ($1.tokentype == $3.tokentype || ($1.tokentype == TypeFloat && $3.tokentype == TypeInt));
                                else {
                                    printf("Incompatible ASSIGN types: left - (%s : %s), right - (%s: %s)\n",
                                    $1.lexeme, gettypestr($1.tokentype), $3.lexeme, $3.tokentypestr);
                                  }
                              } else yyerror("Type Error :::");


                            }
                | error ';'    {printf("error in statement\n");}
                ;

Expression : Expression '+' Term 
                                  {
                                    $$.tokentype = coercetype('+', $1.tokentype, $3.tokentype);
                                    if($$.tokentype > -1 )
                                      strcpy($$.tokentypestr, $$.tokentype == TypeInt ? "INT" : "FLOAT");

                                    char lexeme[25] = { 0 };
                                    snprintf(lexeme, sizeof(lexeme), "%s %s %s", $1.lexeme, "+", $3.lexeme);
                                    strcpy($$.lexeme, lexeme);
                                  }
            |  Expression '-' Term
                                  {
                                    $$.tokentype = coercetype('-', $1.tokentype, $3.tokentype);
                                    if($$.tokentype > -1 )
                                      strcpy($$.tokentypestr, $$.tokentype == TypeInt ? "INT" : "FLOAT");

                                    char lexeme[25] = { 0 };
                                    snprintf(lexeme, sizeof(lexeme), "%s %s %s", $1.lexeme, "-", $3.lexeme);
                                    strcpy($$.lexeme, lexeme);
                                  }
            |  Term               { $$.tokentype = $1.tokentype; }
            ;

Term : Term '*' Factor
             { 
               $$.tokentype = coercetype('*', $1.tokentype, $3.tokentype);
              if($$.tokentype > -1 )
                strcpy($$.tokentypestr, $$.tokentype == TypeInt ? "INT" : "FLOAT");

              char lexeme[25] = { 0 };
              snprintf(lexeme, sizeof(lexeme), "%s %s %s", $1.lexeme, "*", $3.lexeme);
              strcpy($$.lexeme, lexeme);
             }
  | Term '/' Factor
                    { 
                      $$.tokentype = coercetype('/', $1.tokentype, $3.tokentype);
                      if($$.tokentype > -1 )
                        strcpy($$.tokentypestr, $$.tokentype == TypeInt ? "INT" : "FLOAT");

                      char lexeme[25] = { 0 };
                      snprintf(lexeme, sizeof(lexeme), "%s %s %s", $1.lexeme, "/", $3.lexeme);
                      strcpy($$.lexeme, lexeme);
                    }
  | Factor   { $$.tokentype = $1.tokentype; }
  ;

Factor  : TIdentifier  
                      {
                        if ( intab($1.lexeme) )
                           printf("%s is declared\n", $1.lexeme);
                        else
                           printf("UNDECLARED:: %s \n", $1.lexeme);
                        $$.tokentype = gettype($1.lexeme);
                        if ($$.tokentype > 0 )
                              ;
                        else 
                            yyerror("Type Error :::");
                      }
        | TFloatLiteral { $$.tokentype = TypeFloat; }
        | TIntLiteral   {$$.tokentype = TypeInt;}
        | TTrue  { $$.tokentype = TypeBool; }
        | TFalse { $$.tokentype = TypeBool; }
        | '(' Expression ')'
        ;

%%


int main()
{
  yyparse ();
  printf("---------------------\n");
  showtab();
}

void yyerror(char *s)  /* Called by yyparse on error */
{
  printf ("\terror: %s\n", s);
  printf ("ERROR: %s at line %d\n", s, 123);
}

