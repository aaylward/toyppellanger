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
    private:
      vector<string> tokens;
      size_t position;
      void tokenize(const string& s, vector<string>& v);

    public:
      ToyppelLexer(const string& program);
      vector<string>& getTokens();
      pair<bool, string> nextToken();
  };
}

#endif
