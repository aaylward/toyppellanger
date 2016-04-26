#ifndef TOYPPELBUILTINS
#define TOYPPELBUILTINS

#include <iostream>
#include <utility>
#include <unordered_map>
#include <string>

#include "interpreter.h"

using std::unordered_map;
using std::string;
using std::pair;
using std::make_pair;
using std::cout;
using std::endl;

namespace toyppellanger {

  pair<long double, long double> getNextPair(ToyppelTerpreter &interpreter) {
    long double first = interpreter.getStack().back();
    interpreter.getStack().pop_back();
    long double second = interpreter.getStack().back();
    interpreter.getStack().pop_back();
    return make_pair(first, second);
  }

  void add(ToyppelTerpreter &interpreter) {
    pair<long double, long double> operands = getNextPair(interpreter);
    interpreter.getStack().push_back(operands.first + operands.second);
  }

  void subtract(ToyppelTerpreter &interpreter) {
    pair<long double, long double> operands = getNextPair(interpreter);
    interpreter.getStack().push_back(operands.first - operands.second);
  }

  void multiply(ToyppelTerpreter &interpreter) {
    pair<long double, long double> operands = getNextPair(interpreter);
    interpreter.getStack().push_back(operands.first * operands.second);
  }

  void divide(ToyppelTerpreter &interpreter) {
    pair<long double, long double> operands = getNextPair(interpreter);
    interpreter.getStack().push_back(operands.first / operands.second);
  }

  void printTop(ToyppelTerpreter &interpreter) {
    cout << interpreter.getStack().back() << endl;
  }

  void clear(ToyppelTerpreter &interpreter) {
    interpreter.clearStack();
  }

  void printAndEmptyStack(ToyppelTerpreter &interpreter) {
    while (!interpreter.getStack().empty()) {
      cout << interpreter.getStack().back() << endl;
      interpreter.getStack().pop_back();
    }
  }

  void debugStack(ToyppelTerpreter &interpreter) {
    for (auto item : interpreter.getStack()) {
      cout << "[DEBUG]: " << item << endl;
    }
  }

  void quit(ToyppelTerpreter &interpreter) {
    exit(0);
  }

  unordered_map<string, void (*)(ToyppelTerpreter&)> builtin_functions =
  {
    {"+", add},
    {"-", subtract},
    {"*", multiply},
    {"/", divide},
    {"print",  printTop},
    {"dump",  printAndEmptyStack},
    {"debug",  debugStack},
    {"clear",  clear},
  };
}

#endif
