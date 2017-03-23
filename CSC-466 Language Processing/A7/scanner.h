#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>
#include <string>
#include "token.h"
#include "debug.h"

namespace scanner {

    /* variables */
    char ch;
    int position = -1;
    std::string lexeme;
    std::string input;
    std::string stream;

    /* comparisons */
    bool isdigit(char ch) {
        return ch == '0' || ch == '1' || ch == '2';
    }
    bool isoperator(char ch) {
        return ch == '=' || ch == '+' || ch == '*' || ch == '<';
    }
    bool ispunctuation(char ch) {
        return ch == '.' || ch == ';';
    }
    bool isReservedWord(std::string word) {
        return  word == "program" || word == "begin" || word == "end" ||
                word == "if" || word == "then" || word == "else" ||
                word == "while" || word == "do";
    }

    /* flow control */
    char current() {
        ch = stream[position];
        return ch;
    }
    char next() {
        ch = stream[++position];
        return ch;
    }

    /* state handling */
    void reset() { position = -1; input = ""; stream = ""; }

    /* io helpers */
    void read() { while(std::getline(std::cin, input)) { stream.append(input + "\n"); }; }

    /* error handling */
    void raise(Token token) { debugln("scan error: " + token.lexeme()); }
    
    /* scanners */
    Token scanLetter() {
        lexeme = current();
        next();
        if (((lexeme + current()) != "be") && lexeme[0] >= 'a' && lexeme[0] <= 'c') {
            return Token(TokenKind::Variable, lexeme);
        } else while(std::isalpha(current())) { lexeme += current(); next(); }
        if (isReservedWord(lexeme)) return Token(TokenKind::Reserved, lexeme);
        return Token(TokenKind::Error, "'" + lexeme + "'"); 
    }
    
    Token scanDigit() {
        lexeme = current();
        next();
        if(isdigit(lexeme[0])) { return Token(TokenKind::Digit, lexeme); } 
        return Token(TokenKind::Error, "'" + lexeme + "'");
    }

    Token scanOperator() {
        lexeme = current();
        next();
        if(lexeme == "<") {
            if ((lexeme + current()) == "<=") {
                lexeme += current();
                next();
                return Token(TokenKind::Operator, lexeme);
            } else return Token(TokenKind::Error, "'" + lexeme + "'");
        }
        return Token(TokenKind::Operator, lexeme);
    }

    Token scanPunctuation() {
        lexeme = current();
        next();
        return Token(TokenKind::Punctuation, lexeme);
    }

    Token scanToken() {
        if(std::isalpha(current())) { return scanLetter(); }
        else if(std::isdigit(current())) { return scanDigit(); }
        else if(isoperator(current())) { return scanOperator(); }
        else if(ispunctuation(current())) { return scanPunctuation(); }
        else if(current() == EOF || current() == '\0') { return Token(TokenKind::End, "\0"); }
        else { return Token(TokenKind::Error, "an unknown error occurred with '" + std::string(1, current()) + "'"); }
    }

    Token scan() {
        lexeme = "";
        if (position == -1) { position = 0; read(); }
        while(std::isspace(current())) { next();}
        return scanToken();
    }
}
#endif