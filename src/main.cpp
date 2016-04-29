#include <iostream>

#include "interpreter.h"

using std::string;
using std::istream;
using std::cin;
using std::cout;
using std::getline;
using std::endl;

using toyppellanger::Tokenizer;
using toyppellanger::ToyppelTerpreter;

int main(int argc, char *argv[]) {
  if (argc > 2) {
    cout << "usage: toyp <program>" << endl;
    return -1;
  }

  Tokenizer tokenizer;
  ToyppelTerpreter interpreter(tokenizer);

  if (argc == 2) {
    interpreter.run(argv[1]);
    return 0;
  }

  string lineInput;

  interpreter.prompt();
  while (getline(cin, lineInput)) {
    interpreter.run(lineInput);
    interpreter.prompt();
  }
  interpreter.sayBye();
  return 0;
}

