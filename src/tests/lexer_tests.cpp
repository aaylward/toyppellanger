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

using toyppellanger::ToyppelLexer;

vector<string> getTokens(const string& program) {
  ToyppelLexer lexer;
  lexer.tokenize(program);
  return lexer.getTokens();
}

void report(const char* test, bool& passing, vector<string>& actual, vector<string>& expected) {
  if (actual == expected) {
    cout << "[SUCCESS] : " << test << " ✓" <<endl;
  } else {
    cout << "[FAILURE] : " << test << " ✗" <<endl;
    passing = false;
  }
}

void itCanReadStringsInsideParens(bool& passing) {
  auto program = "yo(\"ham\");";
  vector<string> tokens = getTokens(program);
  vector<string> expected = {"yo", "(", "\"ham\"", ")", ";"};
  report("itCanReadStringsInsideParens", passing, tokens, expected);
}

void itCanReadParensWithAndWithoutSpaces(bool& passing) {
  auto program = "((( )())   )";
  vector<string> tokens = getTokens(program);
  vector<string> expected = {"(", "(", "(", ")", "(", ")", ")", ")"};
  report("itCanReadParensWithAndWithoutSpaces", passing, tokens, expected);
}

int main() {
  bool passing = true;
  itCanReadStringsInsideParens(passing);
  itCanReadParensWithAndWithoutSpaces(passing);
  if (passing) {
    cout << "[LEXER TESTS] : ALL PASSED" << endl;
    return 0;
  }
  cout << "[LEXER TESTS] : FAILED" << endl;
  return -1;
}
