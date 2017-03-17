
%{


typedef struct
{
 char lexeme[25];
 int value;
 int tokentype;
 char tokentypestr[25];
}tstruct ;

#define YYSTYPE  tstruct

#include "w.tab.h"

int lineno = 1;

%}

DIGIT  [0-9]
LETTER      [A-Za-z]

%%



START     { if (88) printf("  -%s\n",yytext); return TStart;}
FINISH    { if (88) printf("  -%s\n",yytext); return TFinish;}
BEGIN     { if (88) printf("  -%s\n",yytext); return TBegin;}
END     { if (88) printf("  -%s\n",yytext); return TEnd;}
INT     { if (88) printf("  -%s\n",yytext); return TIntLiteral;}
FLOAT     { if (88) printf("  -%s\n",yytext); return TFloatLiteral;}
BOOL    { if (88) printf("  -%s\n",yytext); return TBoolLiteral;}
PRINT     { if (88) printf("  -%s\n",yytext); return TPrint;}
PRINTLN    { if (88) printf("  -%s\n",yytext); return TPrintLn;}
IF     { if (88) printf("  -%s\n",yytext); return TIf;}
WHILE    { if (88) printf("  -%s\n",yytext); return TWhile;}
LT     { if (88) printf("  -%s\n",yytext); return TLessThan;}
GT     { if (88) printf("  -%s\n",yytext); return TGreaterThan;}
EQ     { if (88) printf("  -%s\n",yytext); return TEqual;}
":("     { if (88) printf("  -%s\n",yytext); return TFalse;}
":)"     { if (88) printf("  -%s\n",yytext); return TTrue;}
":="     { if (88) printf("  -%s\n",yytext); return TAssign;}

\"([^"]*)\"  { if (88) printf("  -%s\n",yytext); return TStringLiteral;}
{LETTER}+     { if (88) printf("  -%s\n",yytext); strcpy(yylval.lexeme,yytext); return TIdentifier; }
{DIGIT}+     { if (88) printf("  -%s\n",yytext); return TIntLiteral; }
{DIGIT}+\.{DIGIT}{DIGIT} { if(88) if (88) printf("  -%s\n",yytext); return TFloatLiteral; }




@@.*\n     {lineno++;} /* comments  */   


[ \t]     /* ignore whitespace */

\n     { lineno++; yylloc.first_line = lineno;}

<<EOF>>   yyterminate();  /* signal end of dialogue */

.        return yytext[0];

%%



