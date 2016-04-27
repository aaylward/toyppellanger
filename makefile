all:
	g++ -pipe -O2 -std=c++11 -Werror -Wall -g src/lexer.cpp src/interpreter.cpp src/main.cpp -o toyp
