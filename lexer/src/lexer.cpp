#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

static int Lexer::gettok() {
    static int LastChar = ' ';

    // Skip any whitespace.
    while(isspace(LastChar)) {
        LastChar = getchar();
    }

    if (isalpha(LastChar)) {
        IdentifierStr = LastChar;
        while(isalnum(LastChar = getchar())) {
            IdentifierStr += LastChar;
        }

        if (IdentifierStr == "def")
            return tok_def;
        if (IdentifierStr == "extern")
            return tok_extern;

        return tok_identifier;
    }

    if (isdigit(LastChar) || LastChar == '.') {
        while (isdigit(LastChar) || LastChar == '.') {
            IdentifierStr += LastChar;
            LastChar = getchar();
        }

        NumVal = strtod(IdentifierStr.c_str(), 0);
        IdentifierStr = "";
        return tok_number;
    }

    if (LastChar == '#') {
        // Comment, ignore until EOL
        do {
            LastChar = getchar();
        } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF)
            return gettok();
    }

    if (LastChar == EOF)
        return tok_eof;

    // Unidentified character, just return its character code
    int ThisChar = LastChar;
    LastChar = getchar();   // FIXME - why is this line here? Surely it eats one character too many?
    return ThisChar;
}
