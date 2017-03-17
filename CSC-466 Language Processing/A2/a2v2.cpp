#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool isnewline(char c)
{
    return c == '\n';
}

bool isletter(int c)
{
    return (tolower(c) >= 'a') && (tolower(c) <= 'z');
}
bool isoperator(char c)
{
    switch (c)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '<':
    case '>':
    case '!':
    case '=':
        return true;
    default:
        return false;
    }
}

int main()
{
    char c;
    string tokens = "";
    cout << "Start" << endl;
    while (cin.get(c))
    {
        while (!isnewline(c))
        {
            if (isspace(c))
            {
                tokens += "w";
                while (isspace(c) && !isnewline(c))
                {
                    c = cin.get();
                }
            }
            else if (isletter(c))
            {
                tokens += "s";
                while (isletter(c))
                {
                    c = cin.get();
                }
            }
            else if (isdigit(c))
            {
                tokens += "n";
                while (isdigit(c))
                {
                    c = cin.get();
                }
            }
            else if (isoperator(c))
            {
                while (c == '+' || c == '-' ||
                       c == '*' || c == '/' ||
                       c == '<' || c == '>')
                {
                    tokens += "o";
                    c = cin.get();
                }

                string s(1, c);
                s += cin.peek();

                if (s == "!=" || s == "==" ||
                    s == ">=" || s == "<=")
                {
                    tokens += "o";
                    c = cin.get();
                    c = cin.get();
                } 
                else if (c == '=' || c == '!')
                {
                    tokens += "p";
                    c = cin.get();
                }
            }
            else
            {
                tokens += "p";
                c = cin.get();
            }
        }

        if (isnewline(c) && tokens.back() != 'w')
        {
            tokens += "w";
        }

        cout << tokens << endl;

        tokens = "";
    }

    cout << "End" << endl;

    return 0;
}
