#include <vector>
#include <utility>
#include <string>
#include <set>
#include <stdexcept>

#include "lexer.h"

using std::vector;
using std::pair;
using std::set;
using std::make_pair;
using std::string;
using std::runtime_error;

using toyppellanger::ToyppelLexer;

const set<char> WHITESPACE = { ' ', '\t', '\n', '\r', '\0' };

bool blank(bool in_str, char c) {
  return (!in_str && WHITESPACE.find(c) != WHITESPACE.end());
};

bool isParen(bool in_str, char c) {
  return !in_str && (c == '(' || c == ')'); };

bool isStringBoundary(const char& c) {
  return c == '"';
}

bool isStartOfToken(const bool& in_str, const string& s, size_t p) {
  return isParen(in_str, s[p]) || (!blank(in_str, s[p]) && (p == 0 || blank(in_str, s[p-1])));
}

bool isEndOfToken(const bool& in_str, const string& s, size_t p) {
  return p == s.length() - 1 || (isParen(in_str, s[p+1]) || blank(in_str, s[p+1]));
}

ToyppelLexer::ToyppelLexer(const string& program) {
  position = 0;
  tokens = {};
  tokenize(program, tokens);
}

vector<string>& ToyppelLexer::getTokens() {
  return tokens;
}

pair<bool, string> ToyppelLexer::nextToken() {
  if (position >= tokens.size()) {
    return make_pair(false, "");
  }
  return make_pair(true, tokens[position++]);
}

void ToyppelLexer::tokenize(const string& s, vector<string>& tokens) {
  size_t start = 0;
  bool in_string = false;

  for (size_t i=0; i<s.length(); i++) {
    if (blank(in_string, s[i])) {
      start = i+1;
      continue;
    } else if (isStringBoundary(s[i])) {
      if (in_string) {
        tokens.push_back(s.substr(start, i - start + 1));
        start = i + 1;
      } else {
        start = i;
      }
      in_string = !in_string;
      continue;
    } else if (isParen(in_string, s[i])) {
      tokens.push_back(s.substr(i, 1));
      start = i + 1;
      continue;
    }

    if (isStartOfToken(in_string, s, i)) {
      start = i;
    } else if (isEndOfToken(in_string, s, i)) {
      tokens.push_back(s.substr(start, i - start + 1));
      start = i + 1;
    }
  }

  if (in_string) {
    throw runtime_error("unexpected end of input");
  }
}
