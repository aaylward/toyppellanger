#include <vector>
#include <utility>
#include <string>

#include "tokenizer.h"
#include "lexer_utils.h"

using std::vector;
using std::pair;
using std::make_pair;
using std::string;

namespace toyppellanger {
  Tokenizer::Tokenizer() {}

  void Tokenizer::tokenize(const string& line) {
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

  vector<string> Tokenizer::getTokens() {
    return tokens;
  }

  pair<bool, string> Tokenizer::nextToken() {
    if (position >= tokens.size()) {
      return make_pair(false, "");
    }
    return make_pair(true, tokens[position++]);
  }

  void Tokenizer::store(string token) {
    tokens.push_back(token);
  }

  void Tokenizer::onTokenStart(size_t& start, size_t i, char c) {
    start = i;
    if (isStringBoundary(c)) {
      in_string = true;
    }
  }

  void Tokenizer::onTokenEnd(string token) {
    store(leftover_string + token);
    leftover_string = "";
    in_string = false;
  }
}
