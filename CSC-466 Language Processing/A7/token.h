#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum TokenKind {
    Reserved,
    Variable,
    Digit,
    Operator,
    Punctuation,
    End,
    Error,
    None,
};

std::string getKindName(TokenKind kind) {
            switch(kind) {
                case TokenKind::Reserved: return "Reserved";
                case TokenKind::Variable: return "Variable";
                case TokenKind::Digit: return "Digit";
                case TokenKind::Operator: return "Operator";
                case TokenKind::Punctuation: return "Punctuation";
                case TokenKind::End: return "End";
                case TokenKind::Error: return "Error";
                case TokenKind::None: return "None";
            }
        }

class Token {
    private: 
        TokenKind _kind;
        int _line;
        int _column;
        std::string _kindName;
        std::string _lexeme;
    public:
        Token() {
            this->_kind = TokenKind::None;
            this->_kindName = getKindName(this->_kind);
            this->_lexeme = "";
            this->_line = 1;
            this->_column = 1;
        }
        Token(TokenKind kind, std::string lexeme, int line, int column) {
            this->_kind = kind;
            this->_kindName = getKindName(this->_kind);
            this->_lexeme = lexeme;
            this->_line = line;
            this->_column = column;
        }

        std::string lexeme() {
            return this->_lexeme;
        }
        
        TokenKind kind() {
            return this->_kind;    
        }
        std::string kindName() {
            return this->_kindName;
        }
        int line() { return this->_line; }
        
        int column() { return this->_column; }
      
};

#endif