
letter [a-zA-Z]
digit [0-9]
newline [\n]
whitespace [ \t]
other .
%%

{letter}        { printf("L"); }
{digit}         { printf("D"); }
{newline}       { printf("w\n"); }
{whitespace}    { printf("w"); }
{other}         { printf("P"); }

%%
