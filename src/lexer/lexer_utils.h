#ifndef TOYPPELLEXERUTILS
#define TOYPPELLEXERUTILS

#include <string>
#include <set>

using std::string;
using std::set;

namespace toyppellanger {
  const set<char> WHITESPACE;
  bool isParen(char c);
  bool isStringBoundary(const char& c);
  bool blank(const bool in_str, char c);
  bool isStartOfToken(const bool in_str, const string& s, size_t p);
  bool isEndOfToken(const bool in_str, const string& s, size_t p);
}

#endif
