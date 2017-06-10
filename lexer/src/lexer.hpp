enum TokenType {
    tok_eof = -1,

    // Commands
    tok_def = -2,
    tok_extern = -3,

    // Primary
    tok_identifier = -4,
    tok_number = -5,

    tok_unknown = -6,
};

typedef struct {
    TokenType type;
    std::string identifier_string;
    double num_val;
    int char_code;
} Token;

bool operator!= (Token, Token);
std::ostream& operator<< (std::ostream&, Token);

class SourceProvider {
    public:
        virtual int getChar() = 0;
        virtual ~SourceProvider() {};
};

class Lexer {
    public:
        Lexer(SourceProvider* source_provider);
        ~Lexer();
        std::vector<Token> getTokens();
    private:
        SourceProvider *_source_provider;
        Token consumeNextToken();
        void consumeAllTokens();
        bool _consumed_all;
        std::vector<Token> _tokens;
};

//static std::string IdentifierStr;   // Filled in if tok_identifier
//static double NumVal;               // Filled in if tok_number
//
//static int gettok();
