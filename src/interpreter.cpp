#include <iostream>
#include <cstdlib>

#include "interpreter.h"
#include "lang/builtins.h"

using std::unordered_map;
using std::vector;
using std::pair;
using std::string;
using std::stold;
using std::cout;
using std::endl;
using std::exit;

using toyppellanger::ToyppelTerpreter;
using toyppellanger::lang::builtin_functions;

ToyppelTerpreter::ToyppelTerpreter(ToyppelLexer& lexer) : lexer(lexer) {
  addWords(builtin_functions);
}

void ToyppelTerpreter::addWords(unordered_map<string, void (*)(ToyppelTerpreter &interpreter)> tokens) {
  definedFunctions.insert(tokens.begin(), tokens.end());
}

void ToyppelTerpreter::run(const string &program) {
  lexer.tokenize(program);

  for (auto token : lexer.getTokens()) {
    if (definedFunctions.count(token) != 0) {
      definedFunctions[token](*this);
    } else {
      stack.push_back(stold(token));
    }
  }
}

vector<long double>& ToyppelTerpreter::getStack() {
  return stack;
}

void ToyppelTerpreter::printTop() {
  cout << stack.back() << endl;
}

void ToyppelTerpreter::clearStack() {
  stack.clear();
}

void ToyppelTerpreter::debugStack() {
  cout << "[DEBUG]: START" << endl;
  for (auto item : stack) {
    cout << "[DEBUG]: " << item << endl;
  }
  cout << "[DEBUG]: END" << endl;
}

void ToyppelTerpreter::prompt() {
  cout << "> ";
}

void ToyppelTerpreter::sayBye() {
  cout << "bye!" << endl;
}

void ToyppelTerpreter::quit() {
  prompt();
  sayBye();
  exit(0);
}

