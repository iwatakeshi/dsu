
eos q

digit_b10   [0-9]
digit_b16   [0-9a-fA-F]

decimal {digit_b10}+
hex     0x{digit_b16}+
other   .
%%
{eos}         { yyterminate(); }
{decimal}     { printf("DEC: %s\n", yytext); }
{hex}         { printf("HEX: %s\n", yytext); }
{other}         


%%