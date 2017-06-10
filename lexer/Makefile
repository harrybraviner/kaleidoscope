BUILD_DIR=./build
SRC_DIR=./src
CC=clang++ -std=c++14 -Wall

${BUILD_DIR} :
	mkdir ${BUILD_DIR}
	mkdir ${BUILD_DIR}/tests

${BUILD_DIR}/lexer.o : ${SRC_DIR}/lexer.cpp ${BUILD_DIR}
	${CC} $< -c -o $@

${BUILD_DIR}/tests/lexer_test : ${SRC_DIR}/tests/lexer_test.cpp ${BUILD_DIR}/lexer.o
	${CC} $^ -o $@ -l boost_unit_test_framework

tests/tests : tests/tests.cpp
	${CC} tests/tests.cpp lexer.o -lboost_unit_test_framework

clean :
	rm -rf ${BUILD_DIR}
