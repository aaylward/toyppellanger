#include <vector>
#include <utility>
#include <string>
#include <set>

#include "lexer.h"

using std::vector;
using std::pair;
using std::set;
using std::make_pair;
using std::string;

using toyppellanger::ToyppelLexer;

const set<char> WHITESPACE = { ' ', '\t', '\n', '\r', '\0' };

bool blank(const bool in_str, char c) {
  return !in_str && WHITESPACE.find(c) != WHITESPACE.end();
};

bool isParen(char c) {
  return c == '(' || c == ')';
};

bool isStringBoundary(const char& c) {
  return c == '"';
}

bool isStartOfToken(const bool in_str, const string& s, size_t p) {
  return !in_str &&
    (isStringBoundary(s[p]) ||
     isParen(s[p]) ||
     (!blank(in_str, s[p]) && (p == 0 || blank(in_str, s[p-1]) || isParen(s[p-1]))));
}

bool isEndOfToken(const bool in_str, const string& s, size_t p) {
  return (
      (in_str && isStringBoundary(s[p])) ||
      (p == s.length() - 1 && (in_str && isStringBoundary(s[p]))) ||
      (!in_str && (isParen(s[p]) || isParen(s[p+1]))) ||
      (blank(in_str, s[p+1])));
}

ToyppelLexer::ToyppelLexer() {}

void ToyppelLexer::tokenize(const string& line) {
  size_t start = 0;

  for (size_t i=0; i<line.length(); i++) {
    was_in_string = in_string;
    if (blank(in_string, line[i])) {
      continue;
    }

    if (isStartOfToken(in_string, line, i)) {
      onTokenStart(start, i, line[i]);
    }

    if (isEndOfToken(in_string && was_in_string, line, i)) {
      onTokenEnd(line.substr(start, i - start + 1));
    }
  }

  if (in_string) {
    leftover_string += line.substr(start, line.length() - start + 1);
  }
}

vector<string> ToyppelLexer::getTokens() {
  return tokens;
}

pair<bool, string> ToyppelLexer::nextToken() {
  if (position >= tokens.size()) {
    return make_pair(false, "");
  }
  return make_pair(true, tokens[position++]);
}

void ToyppelLexer::store(string token) {
  tokens.push_back(token);
}

void ToyppelLexer::onTokenStart(size_t& start, size_t i, char c) {
  start = i;
  if (isStringBoundary(c)) {
    in_string = true;
  }
};

void ToyppelLexer::onTokenEnd(string token) {
  store(leftover_string + token);
  leftover_string = "";
  in_string = false;
}
