#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

#include "../lexer.h"

using std::vector;
using std::string;
using std::pair;
using std::cout;
using std::endl;

using toyppellanger::ToyppelLangerLexer;

vector<string> getTokens(const string& program) {
  ToyppelLangerLexer l(program);
  vector<string> tokens;

  pair<bool, string> next;

  while ((next = l.nextToken()).first) {
    tokens.push_back(next.second);
  }

  return tokens;
}

void itCanReadStrings() {
  auto program = "yo(\"ham\");";
  vector<string> tokens = getTokens(program);
  vector<string> expected = {"yo", "(", "\"ham\"", ")", ";"};
  assert(tokens == expected);
}

int main() {
  itCanReadStrings();
  cout << "[LEXER TESTS] : ALL PASSED" << endl;
  return 0;
}
