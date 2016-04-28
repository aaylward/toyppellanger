#ifndef TOYPPELLEXER
#define TOYPPELLEXER

#include <vector>
#include <utility>
#include <string>

using std::vector;
using std::pair;
using std::string;

namespace toyppellanger {

  class ToyppelLangerLexer {
    private:
      vector<string> tokens;
      size_t position;
      bool isWhitespace(const char& c);
      bool isParen(const char& c);
      bool isStringBoundary(const char& c);
      bool isStartOfToken(const bool& in_string, const string& s, size_t position);
      bool isEndOfToken(const bool& in_string, const string& s, size_t position);
      vector<string> tokenize(const string& s);

    public:
      ToyppelLangerLexer(const string& program);
      pair<bool, string> nextToken();
  };
}

#endif
