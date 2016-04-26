#include <iostream>

#include "interpreter.h"

using std::unordered_map;
using std::stack;
using std::pair;
using std::string;
using std::to_string;
using std::stold;
using std::cout;
using std::endl;

ToyppelTerpreter::ToyppelTerpreter() {
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

void printStack(ToyppelTerpreter& terp) {
  while (!terp.getStack().empty()) {
    cout << terp.getStack().top() << endl;
    terp.getStack().pop();
  }
}

int main() {
  auto program = "1 432 23 43255 printStack";
  ToyppelTerpreter interpreter = ToyppelTerpreter();
  unordered_map<string, void (*)(ToyppelTerpreter&)> dict = { {"printStack", printStack} };
  interpreter.addWords(dict);
  interpreter.run(program);
  return 0;
}
