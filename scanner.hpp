#include <string>

const int MAX_IDENT_LENGTH = 255;

enum tokenType { op, lessthan, equals, leftparen, rightparen, 
separator, terminator, comma, invalid, type, booleanvalue, booleanop, 
keyword, number, identifier, punctuation};

struct token {
  std::string value;
  enum tokenType type;
  unsigned long line;
};

struct tokenList {
  token item;
  tokenList *next;
};
