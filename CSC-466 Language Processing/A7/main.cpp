#include <iostream>
#include <string>
#include <vector>
#include "scanner.h"
#include "parser.h"
#include "token.h"

int main() {
    // Token current = scanner::scan();
    // while(!current.ended()) {
    //     std::cout << current.kindName() << ": "<< current.lexeme() << std::endl;
    //     current = scanner::scan();
    // }
    // if(current.kind() == TokenKind::Error) {
    //     std::cout << current.kindName() << ": "<< current.lexeme() << std::endl;
    // }
    parser::parse();
    return 0;
}