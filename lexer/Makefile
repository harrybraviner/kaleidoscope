BUILD_DIR=./build
SRC_DIR=./src

${BUILD_DIR} :
	mkdir ${BUILD_DIR}

${BUILD_DIR}/lexer.o : ${SRC_DIR}/lexer.cpp ${BUILD_DIR}
	clang++ $< -c -o $@

tests/tests : tests/tests.cpp
	clang++ tests/tests.cpp lexer.o -lboost_unit_test_framework

clean :
	rm -rf ${BUILD_DIR}
