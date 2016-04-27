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

using toyppellanger::ToyppelLangerLexer;

ToyppelLangerLexer::ToyppelLangerLexer(const string &text) {
  nextWordIndex = 0;
  words = split(text, ' ');
}

pair<bool, string> ToyppelLangerLexer::nextWord() {
  if (nextWordIndex >= words.size()) {
    return make_pair(false, "");
  }
  return make_pair(true, words[nextWordIndex++]);
}

vector<string> ToyppelLangerLexer::split(const string &s, char delim) {
  stringstream ss(s);
  string item;
  vector<string> elems;
  while (getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}
