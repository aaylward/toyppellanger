#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

#include "../lexer/tokenizer.h"

using std::vector;
using std::string;
using std::pair;
using std::cout;
using std::endl;

using toyppellanger::Tokenizer;

#define DEBUG for(auto t : tokens) cout << t << endl;

vector<string> getTokens(const string& program) {
  Tokenizer tokenizer;
  tokenizer.tokenize(program);
  return tokenizer.getTokens();
}

void report(const char* test, bool& passing, vector<string>& actual, vector<string>& expected) {
  if (actual == expected) {
    cout << "[SUCCESS] : " << test << " ✓" << endl;
  } else {
    cout << "[FAILURE] : " << test << " ✗" << endl;
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

void itCanReadLetStatements(bool& passing) {
  auto program = "let a 1";
  vector<string> tokens = getTokens(program);
  vector<string> expected = {"let", "a", "1"};
  report("itCanReadLetStatements", passing, tokens, expected);
}

void itCanReadStringsAcrossTwoLines(bool& passing) {
  Tokenizer tokenizer;
  tokenizer.tokenize("Ralph said, \"Hello, ");
  tokenizer.tokenize("World!\"()");
  vector<string> tokens = tokenizer.getTokens();
  vector<string> expected = {"Ralph", "said,", "\"Hello, World!\"", "(", ")"};
  report("itCanReadStringsAcrossTwoLines", passing, tokens, expected);
}

void itCanReadStringsAcrossMoreThanTwoLines(bool& passing) {
  Tokenizer tokenizer;
  tokenizer.tokenize("Ralph said, \"Hello, ");
  tokenizer.tokenize("123 ");
  tokenizer.tokenize("World!\"()");
  vector<string> tokens = tokenizer.getTokens();
  vector<string> expected = {"Ralph", "said,", "\"Hello, 123 World!\"", "(", ")"};
  report("itCanReadStringsAcrossMoreThanTwoLines", passing, tokens, expected);
}

void itCanReadStringsJammedTogether(bool& passing) {
  vector<string> tokens = getTokens("\"1\"\"2*(\"()\"3\"\"4\"");
  vector<string> expected = {"\"1\"", "\"2*(\"", "(", ")", "\"3\"", "\"4\""};
  report("itCanReadStringsJammedTogether", passing, tokens, expected);
}

int main() {
  bool passing = true;
  itCanReadStringsInsideParens(passing);
  itCanReadParensWithAndWithoutSpaces(passing);
  itCanReadLetStatements(passing);
  itCanReadStringsAcrossTwoLines(passing);
  itCanReadStringsAcrossMoreThanTwoLines(passing);
  itCanReadStringsJammedTogether(passing);
  if (passing) {
    cout << "[LEXER TESTS] : ALL PASSED" << endl;
    return 0;
  }
  cout << "[LEXER TESTS] : FAILED" << endl;
  return -1;
}
