#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE lexer_test
#include <boost/test/unit_test.hpp>
#include "../lexer.hpp"

BOOST_AUTO_TEST_CASE ( get_comment ) {
    SourceProvider *srcProv = StringSourceProvider("# some comment\n");

    Lexer lexer(srcProv);


}
