#include <iostream>
#include <cstdlib>

#include "interpreter.h"
#include "lang/builtins.h"

using std::unordered_map;
using std::vector;
using std::pair;
using std::make_pair;
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
  pair<bool, string> nextTokenMaybe;
  string token;

  while ((nextTokenMaybe = lexer.nextToken()).first) {
    token = nextTokenMaybe.second;
    if (definedFunctions.count(token) != 0) {
      definedFunctions[token](*this);
    } else if (token == "let") {
      string name = lexer.nextToken().second;
      long double value = stold(lexer.nextToken().second);
      define(name, value);
    } else if (definedVariables.count(token) == 1) {
      stack.push_back(definedVariables[token]);
    } else {
      stack.push_back(stold(token));
    }
  }
}

vector<long double>& ToyppelTerpreter::getStack() {
  return stack;
}

void ToyppelTerpreter::define(string name, long double value) {
  definedVariables.insert(make_pair(name, value));
}

void ToyppelTerpreter::printTop() {
  cout << stack.back() << endl;
}

void ToyppelTerpreter::clearStack() {
  stack.clear();
}

void ToyppelTerpreter::debugStack() {
  cout << "[DEBUG]: START" << endl;
  for (auto& item : stack) {
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

