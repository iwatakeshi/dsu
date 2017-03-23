
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

%}

DIGIT  [0-9]
UPPERCASELETTER [A-Z]
LOWERCASELETTER [a-z]
LETTER      [A-Za-z]

%%



START       { return TStart;}
FINISH      { return TFinish;}
BEGIN       { return TBegin;}
END         { return TEnd;}
INT         { return TIntLiteral;}
FLOAT       { return TFloatLiteral;}
BOOL        { return TBoolLiteral;}
PRINT       { return TPrint;}
PRINTLN     { return TPrintLn;}
IF          { return TIf;}
WHILE       { return TWhile;}
LT          { return TLessThan;}
GT          { return TGreaterThan;}
EQ          { return TEqual;}
":("        { return TFalse;}
":)"        { return TTrue;}
":="        { return TAssign;}

\"([^"]*)\" { return TStringLiteral;}
{LETTER}+   { strcpy(yylval.lexeme,yytext); return TIdentifier; }
{DIGIT}+    { return TIntLiteral; }
{DIGIT}+\.{DIGIT}{DIGIT} { return TFloatLiteral; }




@@.*\n   {} /* comments  */   


[ \t]     /* ignore whitespace */

\n       {}

<<EOF>>   yyterminate();  /* signal end of dialogue */

.         return yytext[0];

%%



