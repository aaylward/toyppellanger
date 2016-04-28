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
  vector<string> tokens;

  size_t start = 0;
  bool in_string = false;

  for (size_t i=0; i<s.length(); i++) {
    if (in_string) {
      if (isStringBoundary(s[i])) {
        tokens.push_back(s.substr(start, i - start + 1));
        start = i + 1;
        in_string = false;
      }
      continue;
    } else if (isStringBoundary(s[i])) {
      start = i;
      in_string = true;
    } else if (isParen(s[i])) {
      tokens.push_back(s.substr(i, 1));
      start = i + 1;
    } else if (isWhitespace(s[i])) {
      start = i + 1;
    } else if (isStartOfToken(in_string, s, i)) {
      start = i;
    }

    if (isEndOfToken(in_string, s, i)) {
      tokens.push_back(s.substr(start, i - start + 1));
      start = i + 1;
    }
  }

  if (in_string) {
    throw runtime_error("unexpected end of input");
  }

  return tokens;
}

bool ToyppelLangerLexer::isWhitespace(const char& c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\0';
}

bool ToyppelLangerLexer::isStartOfToken(const bool& in_string, const string& s, size_t position) {
  return !in_string && (isParen(s[position]) || (!isWhitespace(s[position]) && (position == 0 || isWhitespace(s[position - 1]))));
}

bool ToyppelLangerLexer::isEndOfToken(const bool& in_string, const string& s, size_t position) {
  return !in_string && (position == s.length() - 1 || (isParen(s[position + 1]) || isWhitespace(s[position+1])));
}

bool ToyppelLangerLexer::isParen(const char& c) {
  return c == '(' || c == ')';
}

bool ToyppelLangerLexer::isStringBoundary(const char& c) {
  return c == '"';
}
