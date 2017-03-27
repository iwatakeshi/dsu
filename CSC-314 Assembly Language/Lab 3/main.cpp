#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>

extern "C" int _replaceChar(
    const char *text, 
    unsigned int length, 
    char character, 
    char replacement
);


int main() {
    char character, replacement/*, text[1000]*/;
    std::string text;
    int length;

    printf("Enter the character to replace: ");
    std::cin >> character;
    printf("\n");
    
    printf("Enter the replacement character: ");
    std::cin >> replacement;
    printf("\n");

    printf("Enter the text to search and replace: \n");
    /* http://stackoverflow.com/a/6649914/1251031 */
    std::cin.ignore();
    std::getline(std::cin, text);
    auto result = _replaceChar(text.c_str(), std::strlen(text.c_str()), character, replacement);
    std::cout << "Replaced " << result << " '" << character << "'s in " << text.c_str() << std::endl;
    
    return 0;
}