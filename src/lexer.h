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
      vector<string> words;
      size_t nextWordIndex;
      vector<string> split(const string &s, char delim);

    public:
      ToyppelLangerLexer(const string &text);
      pair<bool, string> nextWord();
  };
}

#endif