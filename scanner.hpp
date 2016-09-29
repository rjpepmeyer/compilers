#include <string>

enum tokenType { op, lessthan, equals, leftparen, rightparen, 
separator, terminator, comma, invalid, type, booleanvalue, 
booleanop, keyword, number, invalidnum, identifier};

struct token {
  std::string value;
  enum tokenType type;
  unsigned long line;
};

struct tokenList {
  token item;
  tokenList *next;
};
