#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <cstdlib>
#include <cstdio>
#include "scanner.h"
#include "token.h"
#include "debug.h"
using scanner::scan;

namespace parser {
    
    Token currentToken;
    int references = 0;
    int assignments = 0;

    /* flow control */
    void accept() {
        currentToken = scan();
    }

    /* comparisons */
    bool match(TokenKind kind) {
        return currentToken.kind() == kind;
    }
    bool match(TokenKind kind, std::string lexeme) {
        return currentToken.kind() == kind && currentToken.lexeme() == lexeme;
    }

    /* state handling */
    void reset() {
        references = 0;
        assignments = 0;
        currentToken = Token();
        scanner::reset();
    }
    
    /* error handling */
    void raise(std::string expected) {
        debugln("parse error: expected " + expected + " but found " + currentToken.lexeme());
        exit(1);
    }

    void expect(TokenKind kind) {
        if (match(kind)) accept();
        else raise(getKindName(kind));
    }
    void expect(TokenKind kind, std::string lexeme) {
        if (match(kind)) accept();
        else raise(getKindName(kind) + " '" + lexeme + "'");
    }

    /* Forward declarations */
    void parseProgram();
    void parseBlock();
    void parseStatementList();
    void parseStatements();
    void parseStatement();
    void parseAssignment();
    void parseIfStatement();
    void parseWhileStatement();
    void parseCondition();
    void parseExpression();
    void parseVariable();
    void parseDigit();

    /* ----- Program----- */
    void parse() {
        currentToken = scan();
        if(currentToken.kind() == TokenKind::Error) {
            scanner::raise(currentToken);
        } else {
            parseProgram();
            printf("%d assignment(s), %d variable reference(s)\n", assignments, references);
        }
        reset();
    }

    void parseProgram() {
        expect(TokenKind::Reserved, "program");
        parseBlock();
        expect(TokenKind::Punctuation, ".");
    }
    void parseBlock() {
        expect(TokenKind::Reserved, "begin");
        parseStatementList();
        expect(TokenKind::Reserved, "end");
    }
    void parseStatementList() {
        parseStatement();
        parseStatements();
    }
    /* alias for morestmts */
    void parseStatements() {
        while(match(TokenKind::Punctuation, ";")) {
            accept();
            parseStatementList();
        }
    }
    void parseStatement() {
        switch(currentToken.kind()) {
            case TokenKind::Variable:
                parseAssignment();
                return;
            case TokenKind::Reserved:
                if(currentToken.lexeme() == "if") {
                    parseIfStatement();
                    return;
                } else if(currentToken.lexeme() == "while") {
                    parseWhileStatement();
                    return;
                } else if(currentToken.lexeme() == "begin") {
                    parseBlock();
                    return;
                } else raise("Reserved 'if', 'while', or 'begin'");
                return;
            default: raise("Variable or Reserved");
            return;
        }
    }
    void parseAssignment() {
        parseVariable();
        references++;
        expect(TokenKind::Operator, "=");
        parseExpression();
        assignments++;
    }
    void parseIfStatement() {
        expect(TokenKind::Reserved, "if");
        parseCondition();
        expect(TokenKind::Reserved, "then");
        parseStatement();
        expect(TokenKind::Reserved, "else");
        parseStatement();
    }
    void parseWhileStatement() {
        expect(TokenKind::Reserved, "while");
        parseCondition();
        expect(TokenKind::Reserved, "do");
        parseStatement();
    }
    /* alias for testexpr */
    void parseCondition() {
        expect(TokenKind::Variable);
        references++;
        expect(TokenKind::Operator, "<=");
        parseExpression();
        return;
    }
    void parseExpression() {
        switch(currentToken.kind()) {
            case TokenKind::Operator:
                if(currentToken.lexeme() == "+" || currentToken.lexeme() == "*") {
                    accept();
                    parseExpression();
                    parseExpression();
                    return;
                } else raise("Operator '+' or '*'");
                return;
            case TokenKind::Variable:
                parseVariable();
                references++;
                return;
            case TokenKind::Digit:
                parseDigit();
                return;
            default:
                raise("Operator, Variable, or Digit");
                return;
        }
    }
    void parseVariable() {
        expect(TokenKind::Variable);
    }
    void parseDigit() {
        expect(TokenKind::Digit);
    }
}

#endif