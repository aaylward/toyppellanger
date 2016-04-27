#ifndef TOYPPELTERPRETER
#define TOYPPELTERPRETER

#include <unordered_map>
#include <vector>
#include <string>

#include "lexer.h"

using std::unordered_map;
using std::vector;
using std::string;

namespace toyppellanger {

  class ToyppelTerpreter {
    private:
      unordered_map<string, void (*)(ToyppelTerpreter&)> definedWords = {};
      vector<long double> stack = {};

    public:
      ToyppelTerpreter();
      void addWords(unordered_map<string, void (*)(ToyppelTerpreter &interpreter)> definedTokens);
      void run(const string &program);
      vector<long double>& getStack();
      void printTop();
      void clearStack();
      void debugStack();
      void prompt();
      void sayBye();
      void quit();
  };
}

#endif
