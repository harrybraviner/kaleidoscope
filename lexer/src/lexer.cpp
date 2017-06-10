#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <boost/test/unit_test.hpp>

#include "lexer.hpp"

using namespace std;

bool operator== (Token t1, Token t2) {
    if (   t1.type == t2.type
        && t1.identifier_string == t2.identifier_string
        && t1.num_val == t2.num_val )
        return true;
    else
        return false;
}

bool operator!= (Token t1, Token t2) {
    return !(t1 == t2);
}

std::ostream& operator<< (std::ostream& os, Token t) {
    os << "{" << t.type << ", " << t.identifier_string
       << ", " << t.num_val << "}";
    return os;
}

namespace boost{ namespace test_tools {
template<>
struct tt_detail::print_log_value<Token> {
    void operator() (std::ostream& os, Token const& t) {
        ::operator<<(os, t);
    }
};
}}

Lexer::Lexer(SourceProvider* source_provider)
: _source_provider(source_provider),
  _consumed_all(false)
{
}

vector<Token> Lexer::getTokens() {
    this->consumeAllTokens();
    return vector<Token>(this->_tokens);
}

Lexer::~Lexer() {
    delete _source_provider;
}

void Lexer::consumeAllTokens() {
    if (_consumed_all) return;

    Token next_token;
    do {
        next_token = this->consumeNextToken();
        _tokens.push_back(next_token);
    } while (next_token.type != tok_eof);

    _consumed_all = true;
}

Token Lexer::consumeNextToken() {

    int LastChar = ' ';

    // Skip any whitespace.
    while(isspace(LastChar)) {
        LastChar = this->_source_provider->getChar();
    }
    
    if (LastChar == '#') {
        // Comment, ignore until EOL
        do {
            LastChar = this->_source_provider->getChar();
        } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF)
            return this->consumeNextToken();
    }

    // Identifiers
    if (isalpha(LastChar) || LastChar == '_') {
        string ident_str;
        while(isalnum(LastChar) || LastChar == '_') {
            ident_str += LastChar;
            LastChar = this->_source_provider->getChar();
        }

        if (ident_str == "def")
            return {tok_def, "", 0.0, 0};
        if (ident_str == "extern")
            return {tok_extern, "", 0.0, 0};

        return {tok_identifier, ident_str, 0.0, 0} ;
    }

    if (isdigit(LastChar) || LastChar == '.') {
        string num_str;
        while (isdigit(LastChar) || LastChar == '.') {
            num_str += LastChar;
            LastChar = this->_source_provider->getChar();
        }

        double num_val = strtod(num_str.c_str(), 0);
        return {tok_number, "", num_val, 0};
    }

    if (LastChar == EOF)
        return {tok_eof, "", 0.0, 0};

    return {tok_unknown, "", 0.0, LastChar}; // Unknown, pass out the character code
}
//
//    if (LastChar == EOF)
//        return tok_eof;
//
//    // Unidentified character, just return its character code
//    int ThisChar = LastChar;
//    LastChar = getchar();   // FIXME - why is this line here? Surely it eats one character too many?
//    return ThisChar;
//}
