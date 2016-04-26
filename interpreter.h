#ifndef TOYPPELTERPRETER
#define TOYPPELTERPRETER

#include <unordered_map>
#include <stack>
#include <string>

#include "lexer.h"

using std::unordered_map;
using std::stack;
using std::string;

class ToyppelTerpreter {
  private:
    unordered_map<string, void (*)(ToyppelTerpreter&)> definedWords = {};
    stack<long double> numbers = {};
  
  public:
    ToyppelTerpreter();
    void addWords(unordered_map<string, void (*)(ToyppelTerpreter &interpreter)> definedTokens);
    void run(const string &program);
    stack<long double>& getStack();
};

#endif
