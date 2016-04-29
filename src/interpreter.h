#ifndef TOYPPELTERPRETER
#define TOYPPELTERPRETER

#include <unordered_map>
#include <vector>
#include <set>
#include <string>

#include "lexer.h"

using std::unordered_map;
using std::vector;
using std::set;
using std::string;

namespace toyppellanger {
  class ToyppelTerpreter {
    public:
      ToyppelTerpreter(ToyppelLexer& lexer);
      void addWords(unordered_map<string, void (*)(ToyppelTerpreter& interpreter)> definedTokens);
      void run(const string& program);
      vector<long double>& getStack();
      void define(string name, long double value);
      void define(string name, string definition);
      void printTop();
      void clearStack();
      void debugStack();
      void prompt();
      void sayBye();
      void quit();
      void pop();

    private:
      ToyppelLexer& lexer;
      unordered_map<string, void (*)(ToyppelTerpreter&)> definedFunctions = {};
      unordered_map<string, long double> definedVariables = {};
      unordered_map<string, string> definedMacros = {};
      vector<long double> stack = {};
  };
}

#endif
