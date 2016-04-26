#ifndef TOYPPLELEXER
#define TOYPPLELEXER

#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <string>

using std::vector;
using std::pair;
using std::string;

class ToyppleLangerLexer {
  private:
    vector<string> words;
    size_t nextWordIndex;
    vector<string> split(const string &s, char delim);

  public:
    ToyppleLangerLexer(const string &text);
    pair<bool, string> nextWord();
};

#endif
