
letter [a-zA-Z]
digit [0-9]
operator (\+|-|\*|\/|%|<|<=|>|>=|==|!=)
whitespace [ \t\v\r]
other .

%%
\n                          { printf("w\n"); }
{whitespace}+               { printf("w"); }
{digit}+                    { printf("n"); }
{letter}+                   { printf("s"); }
{operator}                  { printf("o"); }
{other}                     { printf("p"); }
%%
