#ifndef DEBUG_H
#define DEBUG_H
#include <iostream>
#include <string>

void debug(int number) { std:: cout << number; }
void debugln(int number) { std:: cout << number << std:: endl; }

void debug(char ch) { std:: cout << ch; }
void debugln(char ch) { std:: cout << ch << std:: endl; }

void debug(std::string output) { std:: cout << output; }
void debugln(std::string output, int number) { debug(output); debugln(number); }
void debugln(std::string output) { std:: cout << output << std:: endl; }
#endif