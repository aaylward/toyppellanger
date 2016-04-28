#ifndef TOYPPELLEXER
#define TOYPPELLEXER

#include <vector>
#include <utility>
#include <string>

using std::vector;
using std::pair;
using std::string;

namespace toyppellanger {
  class ToyppelLexer {
    public:
      ToyppelLexer();
      void tokenize(const string& program);
      vector<string> getTokens();
      pair<bool, string> nextToken();

    private:
      vector<string> tokens = {};
      size_t position = 0;
  };
}

#endif
