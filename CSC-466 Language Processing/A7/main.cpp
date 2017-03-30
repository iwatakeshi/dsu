#include <iostream>
#include <string>
#include "scanner.h"
#include "parser.h"
#include "token.h"

int main() {
    // Token current;
    // while(!scanner::eof()) {
    //     current = scanner::scan();
    //     std::cout << current.kindName() << ": "<< current.lexeme() << std::endl;
    // }
    // if(current.kind() == TokenKind::Error) {
    //     std::cout << current.kindName() << ": "<< current.lexeme() << std::endl;
    // }
    parser::parse();
    return 0;
}