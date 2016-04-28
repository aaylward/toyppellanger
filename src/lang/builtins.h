#ifndef TOYPPELBUILTINS
#define TOYPPELBUILTINS

#include <unordered_map>
#include <string>

#include "../interpreter.h"
#include "math.h"

using std::unordered_map;
using std::string;

namespace toyppellanger {
  namespace lang {

    unordered_map<string, void (*)(ToyppelTerpreter&)> builtin_functions =
    {
      {"+", add},
      {"-", subtract},
      {"*", multiply},
      {"/", divide},
      {"print",  [](ToyppelTerpreter& t) -> void {t.printTop();}},
      {"debug",  [](ToyppelTerpreter& t) -> void {t.debugStack();}},
      {"clear",  [](ToyppelTerpreter& t) -> void {t.clearStack();}},
      {"quit",  [](ToyppelTerpreter& t) -> void {t.quit();}},
    };
  }
}

#endif
