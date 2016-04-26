#include <iostream>

#include "interpreter.h"
#include "builtins.h"

using std::unordered_map;
using std::stack;
using std::pair;
using std::string;
using std::to_string;
using std::stold;
using std::cout;
using std::endl;

using toyppellanger::ToyppelTerpreter;
using toyppellanger::builtin_functions;

ToyppelTerpreter::ToyppelTerpreter() {
  addWords(builtin_functions);
}

void ToyppelTerpreter::addWords(unordered_map<string, void (*)(ToyppelTerpreter &interpreter)> tokens) {
  definedWords.insert(tokens.begin(), tokens.end());
}

void ToyppelTerpreter::run(const string &program) {
  ToyppelLangerLexer lexer(program);
  pair<bool, string> nextWordMaybe;

  while ((nextWordMaybe = lexer.nextWord()).first) {
    if (definedWords.count(nextWordMaybe.second) != 0) {
      definedWords[nextWordMaybe.second](*this);
    } else {
      long double ld = stold(nextWordMaybe.second);
      numbers.push(ld);
    }
  }
}

stack<long double>& ToyppelTerpreter::getStack() {
  return numbers;
}

int main() {
  auto program = "1 432 23 43255 printAndEmptyStack";
  ToyppelTerpreter interpreter;
  interpreter.run(program);
  return 0;
}
