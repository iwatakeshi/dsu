#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    char c;
    string tokens = "";
    printf("Start\n");
    while (cin.get(c))
    {
        if ((tolower(c) >= 'a') && tolower(c) <= 'z')
        {
            tokens += "L";
        }
        else if (c >= '0' && c <= '9')
        {
            tokens += "D";
        }
        else if (isspace(c))
        {
            tokens += "W";
        }
        else
        {
            tokens += "P";
        }

        if (c == '\n')
        {
            cout << tokens << endl;
            tokens = "";
        }
    }

    cout << "End" << endl;

    return 0;
}

