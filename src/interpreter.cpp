#include <iostream>
#include <cstdlib>

#include "interpreter.h"
#include "lang/builtins.h"

using std::unordered_map;
using std::vector;
using std::pair;
using std::string;
using std::to_string;
using std::stold;
using std::cout;
using std::exit;

using toyppellanger::ToyppelTerpreter;
using toyppellanger::lang::builtin_functions;

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
      stack.push_back(ld);
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
  for (auto item : stack) {
    cout << "[DEBUG]: " << item << endl;
  }
}

void ToyppelTerpreter::prompt() {
  cout << "> ";
}

void ToyppelTerpreter::quit() {
  exit(0);
}

