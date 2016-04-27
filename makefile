all:
	g++ -pipe -O2 -std=c++11 -Werror -Wall -g lexer.cpp interpreter.cpp main.cpp -o toyp
