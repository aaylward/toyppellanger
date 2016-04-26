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
    long double first = interpreter.getStack().top();
    interpreter.getStack().pop();
    long double second = interpreter.getStack().top();
    interpreter.getStack().pop();
    return make_pair(first, second);
  }

  void add(ToyppelTerpreter &interpreter) {
    pair<long double, long double> operands = getNextPair(interpreter);
    interpreter.getStack().push(operands.first + operands.second);
  }

  void subtract(ToyppelTerpreter &interpreter) {
    pair<long double, long double> operands = getNextPair(interpreter);
    interpreter.getStack().push(operands.first - operands.second);
  }

  void multiply(ToyppelTerpreter &interpreter) {
    pair<long double, long double> operands = getNextPair(interpreter);
    interpreter.getStack().push(operands.first * operands.second);
  }

  void divide(ToyppelTerpreter &interpreter) {
    pair<long double, long double> operands = getNextPair(interpreter);
    interpreter.getStack().push(operands.first / operands.second);
  }

  void printTop(ToyppelTerpreter &interpreter) {
    cout << interpreter.getStack().top() << endl;
  }

  void printAndEmptyStack(ToyppelTerpreter& interpreter) {
    while (!interpreter.getStack().empty()) {
      cout << interpreter.getStack().top() << endl;
      interpreter.getStack().pop();
    }
  }

  unordered_map<string, void (*)(ToyppelTerpreter&)> builtin_functions =
  {
    {"+", add},
    {"-", subtract},
    {"*", multiply},
    {"/", divide},
    {"printTop",  printTop},
    {"printAndEmptyStack",  printAndEmptyStack},
  };
}

#endif
