#ifndef TOYPPELMATH
#define TOYPPELMATH

#include <utility>

#include "../interpreter.h"

using std::pair;
using std::make_pair;

namespace toyppellanger {
  namespace lang {

    pair<long double, long double> getNextPair(ToyppelTerpreter& interpreter) {
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
  }
}

#endif
