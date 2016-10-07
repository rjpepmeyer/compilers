#include <string>

const int MAX_IDENT_LENGTH = 255;

enum tokenType { op = 0, lessthan, equals, leftparen, rightparen, 
separator, terminator, comma, invalid, type, booleanvalue, booleanop, 
keyword, number, identifier, punctuation, eos, program, definitions, 
def, formals, nonemptyformals, nonemptyformalsprime, formal, body, 
statementlist, typent, expr, exprprime, simpleexpr, simpleexprprime, 
term, termprime, factor, factorprime, actuals};
/*
enum nonTerminalTokenType {program, definitions, def, formals, 
nonemptyformals, nonemptyformals-prime, formal, body, statement-list, 
type, expr, expr-prime, simple-expr, simple-expr-prime, term, 
term-prime, factor, factor-prime, actuals};
*/
class token {
  public:
    std::string value;
    enum tokenType type;
    unsigned long line;
};

class tokenList {
  public:
    token item;
    tokenList *next;
    token peek() { // Returns token from next node in list
      return (*next).item;
    }
    void advance() { // Replaces self with next node in list
      item = (*next).item;
      next = (*next).next;
    }
};

class tokenStack {
    tokenList *top;
  public:
    void push (token);
    token pop ();
};

void tokenStack::push(token input) {
  tokenList *next = top;
  top = new tokenList;
  top->item = input;
  top->next = next;
}

token tokenStack::pop() {
  tokenList *toFree = top;
  token result = top->item;
  top = top->next;
  delete toFree;
  return result;
}
