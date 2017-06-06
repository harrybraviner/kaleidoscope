#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE lexer_tests
#include <boost/test/unit_test.hpp>
#include "../lexer.hpp"

BOOST_AUTO_TEST_CASE (test1) {
    char *source = "def\nextern 1.76 9.8 53 def\n\n # hello def\nextern\n";

    BOOST_CHECK_EQUAL_COLLECTIONS ( arr1, arr1 + 1, arr2, arr2 + 1 );
}
