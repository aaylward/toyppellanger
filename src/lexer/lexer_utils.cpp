#include <string>
#include <set>

using std::string;
using std::set;

namespace toyppellanger {
  const set<char> WHITESPACE = { ' ', '\t', '\n', '\r', '\0' };

  bool isParen(char c) {
    return c == '(' || c == ')';
  }

  bool isStringBoundary(const char& c) {
    return c == '"';
  }

  bool blank(const bool in_str, char c) {
    return !in_str && WHITESPACE.find(c) != WHITESPACE.end();
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
}
