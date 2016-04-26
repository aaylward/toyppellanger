#include <iostream>

#include "interpreter.h"

using std::string;
using std::istream;
using std::cin;
using std::cout;
using std::getline;
using std::endl;

using toyppellanger::ToyppelTerpreter;

void prompt() {
  cout << "> ";
}

int main(int argc, char *argv[]) {
  if (argc > 2) {
    cout << "usage: toyp <program>" << endl;
    return -1;
  }

  ToyppelTerpreter interpreter;

  if (argc == 2) {
    interpreter.run(argv[1]);
    return 0;
  }

  string lineInput;

  prompt();
  while (getline(cin, lineInput)) {
    interpreter.run(lineInput);
    prompt();
  }
  return 0;
}

