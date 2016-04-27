#include <vector>
#include <utility>
#include <string>
#include <stdexcept>

#include "lexer.h"

using std::vector;
using std::pair;
using std::make_pair;
using std::string;
using std::runtime_error;

using toyppellanger::ToyppelLangerLexer;

ToyppelLangerLexer::ToyppelLangerLexer(const string& program) {
  position = 0;
  tokens = tokenize(program);
}

pair<bool, string> ToyppelLangerLexer::nextToken() {
  if (position >= tokens.size()) {
    return make_pair(false, "");
  }
  return make_pair(true, tokens[position++]);
}

vector<string> ToyppelLangerLexer::tokenize(const string& s) {
  vector<string> _tokens;

  size_t start = 0;
  bool in_string = false;

  for (size_t i=0; i<s.length(); i++) {
    if (in_string) {
      if (s[i] == '"') {
        _tokens.push_back(s.substr(start, i - start + 1));
        start = i + 1;
        in_string = false;
      }
      continue;
    }

    if (s[i] == '"') {
      start = i;
      in_string = true;
      continue;
    }

    if (isParen(s[i])) {
      _tokens.push_back(s.substr(i, 1));
      start = i + 1;
      continue;
    }

    if (isWhitespace(s[i])) {
      start = i + 1;
      continue;
    }

    if (isStartOfToken(s, i)) {
      start = i;
    }

    if (isEndOfToken(s, i)) {
      _tokens.push_back(s.substr(start, i - start + 1));
      start = i + 1;
      continue;
    }
  }

  if (in_string) {
    throw runtime_error("unexpected end of input");
  }

  return _tokens;
}

bool ToyppelLangerLexer::isWhitespace(const char& c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\0';
}

bool ToyppelLangerLexer::isStartOfToken(const string& s, size_t position) {
  return isParen(s[position]) || (!isWhitespace(s[position]) && (position == 0 || isWhitespace(s[position - 1])));
}

bool ToyppelLangerLexer::isEndOfToken(const string& s, size_t position) {
  return position == s.length() - 1 || (isParen(s[position + 1]) || isWhitespace(s[position+1]));
}

bool ToyppelLangerLexer::isParen(const char& c) {
  return c == '(' || c == ')';
}
