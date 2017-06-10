#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE lexer_test
#include <boost/test/unit_test.hpp>
#include "../lexer.hpp"

using namespace std;

class StringSourceProvider : public SourceProvider {
    public:
        StringSourceProvider(string str);
        ~StringSourceProvider();
        int getChar();
    private:
        string _str;
        unsigned int _cursor;
        unsigned int _length;
};

BOOST_AUTO_TEST_CASE ( string_source_provider ) {
    SourceProvider *src_prov = new StringSourceProvider("abc\n");

    BOOST_CHECK_EQUAL('a', src_prov->getChar());
    BOOST_CHECK_EQUAL('b', src_prov->getChar());
    BOOST_CHECK_EQUAL('c', src_prov->getChar());
    BOOST_CHECK_EQUAL('\n', src_prov->getChar());
    BOOST_CHECK_EQUAL(-1, src_prov->getChar());
    BOOST_CHECK_EQUAL(-1, src_prov->getChar());

}

BOOST_AUTO_TEST_CASE ( pure_comments ) {
    SourceProvider *src_prov = new StringSourceProvider("# commment one\n  # comment two");

    vector<Token> expected_tokens;
    expected_tokens.push_back({tok_eof, "", 0.0, 0});

    Lexer lexer(src_prov);

    vector<Token> actual_tokens = lexer.getTokens();

    BOOST_CHECK_EQUAL_COLLECTIONS(expected_tokens.begin(), expected_tokens.end(), actual_tokens.begin(), actual_tokens.end());
}

BOOST_AUTO_TEST_CASE ( number ) {
    SourceProvider *src_prov = new StringSourceProvider("134.56");

    vector<Token> expected_tokens;
    expected_tokens.push_back({tok_number, "", 134.56, 0});
    expected_tokens.push_back({tok_eof, "", 0.0, 0});

    Lexer lexer(src_prov);

    vector<Token> actual_tokens = lexer.getTokens();

    BOOST_CHECK_EQUAL_COLLECTIONS(expected_tokens.begin(), expected_tokens.end(), actual_tokens.begin(), actual_tokens.end());
}

BOOST_AUTO_TEST_CASE ( identifier ) {
    SourceProvider *src_prov = new StringSourceProvider("hello_all Wor1d");

    vector<Token> expected_tokens;
    expected_tokens.push_back({tok_identifier, "hello_all", 0.0, 0});
    expected_tokens.push_back({tok_identifier, "Wor1d", 0.0, 0});
    expected_tokens.push_back({tok_eof, "", 0.0, 0});

    Lexer lexer(src_prov);

    vector<Token> actual_tokens = lexer.getTokens();

    BOOST_CHECK_EQUAL_COLLECTIONS(expected_tokens.begin(), expected_tokens.end(), actual_tokens.begin(), actual_tokens.end());
}

BOOST_AUTO_TEST_CASE ( def_and_extern ) {
    SourceProvider *src_prov = new StringSourceProvider("def extern");

    vector<Token> expected_tokens;
    expected_tokens.push_back({tok_def, "", 0.0, 0});
    expected_tokens.push_back({tok_extern, "", 0.0, 0});
    expected_tokens.push_back({tok_eof, "", 0.0, 0});

    Lexer lexer(src_prov);

    vector<Token> actual_tokens = lexer.getTokens();

    BOOST_CHECK_EQUAL_COLLECTIONS(expected_tokens.begin(), expected_tokens.end(), actual_tokens.begin(), actual_tokens.end());
}


BOOST_AUTO_TEST_CASE ( comment_then_ident ) {
    SourceProvider *src_prov = new StringSourceProvider("# here's a load of comment\n  x_3");

    vector<Token> expected_tokens;
    expected_tokens.push_back({tok_identifier, "x_3", 0.0, 0});
    expected_tokens.push_back({tok_eof, "", 0.0, 0});

    Lexer lexer(src_prov);

    vector<Token> actual_tokens = lexer.getTokens();

    BOOST_CHECK_EQUAL_COLLECTIONS(expected_tokens.begin(), expected_tokens.end(), actual_tokens.begin(), actual_tokens.end());
}

BOOST_AUTO_TEST_CASE ( unknown_token ) {
    SourceProvider *src_prov = new StringSourceProvider(" x_3 / y");

    vector<Token> expected_tokens;
    expected_tokens.push_back({tok_identifier, "x_3", 0.0, 0});
    expected_tokens.push_back({tok_unknown, "", 0.0, '/'});
    expected_tokens.push_back({tok_identifier, "y", 0.0, 0});
    expected_tokens.push_back({tok_eof, "", 0.0, 0});

    Lexer lexer(src_prov);

    vector<Token> actual_tokens = lexer.getTokens();

    BOOST_CHECK_EQUAL_COLLECTIONS(expected_tokens.begin(), expected_tokens.end(), actual_tokens.begin(), actual_tokens.end());
}

BOOST_AUTO_TEST_CASE ( many_tokens ) {
    SourceProvider *src_prov = new StringSourceProvider("x_3 / y # divisison\n# blah blah\ndef f2\ny = x - 7.62 # some stuff\n");

    vector<Token> expected_tokens;
    expected_tokens.push_back({tok_identifier, "x_3", 0.0, 0});
    expected_tokens.push_back({tok_unknown, "", 0.0, '/'});
    expected_tokens.push_back({tok_identifier, "y", 0.0, 0});
    expected_tokens.push_back({tok_def, "", 0.0, 0});
    expected_tokens.push_back({tok_identifier, "f2", 0.0, 0});
    expected_tokens.push_back({tok_identifier, "y", 0.0, 0});
    expected_tokens.push_back({tok_unknown, "", 0.0, '='});
    expected_tokens.push_back({tok_identifier, "x", 0.0, 0});
    expected_tokens.push_back({tok_unknown, "", 0.0, '-'});
    expected_tokens.push_back({tok_number, "", 7.62, 0});
    expected_tokens.push_back({tok_eof, "", 0, 0});

    Lexer lexer(src_prov);

    vector<Token> actual_tokens = lexer.getTokens();

    BOOST_CHECK_EQUAL_COLLECTIONS(expected_tokens.begin(), expected_tokens.end(), actual_tokens.begin(), actual_tokens.end());
}

StringSourceProvider::StringSourceProvider(string str)
: _str(str), _cursor(0)
{
    _length = _str.length();
}

StringSourceProvider::~StringSourceProvider() {}

int StringSourceProvider::getChar() {
    if (_cursor < _length)
        return _str.at(_cursor++);
    else
        return EOF;
}
