all:
	rm -rf build
	mkdir build
	g++ -pipe -O2 -std=c++11 -Werror -Wall -g src/lexer.cpp src/interpreter.cpp src/main.cpp -o build/toyp

install:
	cp build/toyp /usr/local/bin/toyp

test:
	rm -rf testbuild
	mkdir testbuild
	g++ -pipe -O2 -std=c++11 -Werror -Wall -g src/lexer.cpp src/tests/lexer_tests.cpp -o testbuild/lexer_test
	./testbuild/lexer_test

clean:
	rm -rf build
	rm -rf testbuild
