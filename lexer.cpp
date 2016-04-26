#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <string>

#include "lexer.h"

using std::vector;
using std::pair;
using std::make_pair;
using std::string;
using std::stringstream;
using std::getline;

ToyppleLangerLexer::ToyppleLangerLexer(const string &text) {
  words = split(text, ' ');
}

pair<bool, string> ToyppleLangerLexer::nextWord() {
  if (nextWordIndex >= words.size()) {
    return make_pair(false, "");
  }
  return make_pair(true, words[nextWordIndex++]);
}

vector<string> ToyppleLangerLexer::split(const string &s, char delim) {
  stringstream ss(s);
  string item;
  vector<string> elems;
  while (getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

int main() {
  auto program = "This is a cool program { yo };";
  ToyppleLangerLexer lexer(program);
  pair<bool, string> next;
  while ((next = lexer.nextWord()).first) {
    std::cout << next.second << std::endl;
  }
  return 0;
}
