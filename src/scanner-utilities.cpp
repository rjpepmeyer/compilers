#include <string>
#include <ctype.h>

using namespace std;

// Takes a character as an argument
// Returns TRUE if character matches a self deliminating token.
bool isSelfDeliminator(char c) {
  string selfDeliminators = "+-*/<=(),:{;}.";
  for(int i = 0; i < selfDeliminators.length(); i++) {
    if (c == selfDeliminators[i]) return true;
  }
  return false;
}

// Takes a string and returns if it is a valid number
bool isValidNum(string input) {
  // If it starts with leading zeros, it's invalid
  if (!isdigit(input.front())) {
    return false;
  }
  else if (input.length() > 1 && input.front() == '0') {
    return false;
  }
  // If it's longer than ten characters, it exceeds 2^32
  else if (input.length() > 10) {
    return false;
  }
  // If it's ten digits, but larger than 2^32-1 still
  else if (input.length() == 10 && input > "4294967295") {
    return false;
  }
  else {
    // If it contains non digits, it's false
    int i;
    while(i < input.length()) {
      if (!isdigit(input.at(i))) break;
      i++;
    }
    if (i == input.length()) {
      return true;
    }
    else {
      return false;
    }
  }
}

// Returns string of enum
string toString(enum tokenType input) {
  switch(input) {
    case op:           return "<operator>   "; break;
    case lessthan:       return "<less-than>  "; break;
    case equals:         return "<equals>     "; break;
    case leftparen:      return "<left-paren> "; break;
    case rightparen:     return "<right-paren>"; break;
    case separator:      return "<separator>  "; break;
    case terminator:     return "<terminator> "; break;
    case comma:          return "<comma>      "; break;
    case type:           return "<typename>   "; break;
    case booleanvalue:   return "<bool-value> "; break;
    case booleanop:      return "<bool-op>    "; break;
    case keyword:        return "<keyword>    "; break;
    case number:         return "<number>     "; break;
    case identifier:     return "<identifier> "; break;
    case punctuation:    return "<punctuation>"; break;
    case eos:            return "<$>          "; break;
    case program:        return "<program>    "; break;
    case definitions:    return "<definitions>"; break;
    case def:            return "<def>        "; break;
    case formals:        return "<formals>    "; break;
    case nonemptyformals:return "<neformals>  "; break;
    case nonemptyformalsprime:return "<neformals'> "; break;
    case formal:         return "<formal>     "; break;
    case body:           return "<body>       "; break;
    case statementlist:  return "<statmnt-lst>"; break;
    case typent:         return "<type>       "; break;
    case expr:           return "<expression> "; break;
    case exprprime:      return "<expression'>"; break;
    case simpleexpr:     return "<simpleexpr> "; break;
    case simpleexprprime:return "<simpleexpr'>"; break;
    case term:           return "<term>       "; break;
    case termprime:      return "<term'>      "; break;
    case factor:         return "<factor>     "; break;
    case factorprime:    return "<factor'>    "; break;
    case actuals:        return "<actuals>    "; break;
    case nonemptyactuals:return "<neactuals>  "; break;
    case nonemptyactualsprime:return "<neactuals'> "; break;
    case literal:        return "<literal>    "; break;
    case printstatement: return "<prntstatmnt>"; break;
    case makeprogram:    return "<make-program>";break;
    case makeformal:     return "<make-formal>"; break;
    case makeformals:    return "<make-formals>";break;
    case makedef:        return "<make-def>   "; break;
    case makedefs:       return "<make-defs>  "; break;
    case makebody:       return "<make-body>  "; break;
    case makestatement:  return "<make-statement>";break;
    case makestatements: return "<make-statements>";break;
    case makeprint:      return "<make-print> "; break;
    case makereturn:     return "<make-return>"; break;
    case makeif:         return "<make-if>    "; break;
    case makenot:        return "<make-not>   "; break;
    case makefncall:     return "<make-fncall>"; break;
    case makenegate:     return "<make-negate>"; break;
    case makeblock:      return "<make-block> "; break;
    case makebinexp:     return "<make-binexp>"; break;
    case makeexpr:       return "<make-expr>  "; break;
    case makeidentifier: return "<make-identifier>";break;
    case maketype:       return "<make-type>  "; break;
    case makeoperator:   return "<make-operator>";break;
    case makenumber:     return "<make-number>"; break;
    case makeboolean:    return "<make-boolean>";break;
    default:             return "<invalid>    "; break;
    
  }
}

// Function that takes as input a single character token,
// and returns as output a string containing the type of
// the token.
enum tokenType getType(char input) {
  if (input == '+' || input == '-' || input == '*' || 
  input == '/') {
    return op;
  }
  else if (input == '<') {
    return lessthan;
  }
  else if (input == '=') {
    return equals;
  }
  else if (input == '(') {
    return leftparen;
  }
  else if (input == ')') {
    return rightparen;
  }
  else if (input == ':') {
    return separator;
  }
  else if (input == ';') {
    return terminator;
  }
  else if (input == ',') {
    return comma;
  }
  else if (input == '.') {
    return punctuation;
  }
  else {
    return invalid;
  }
}
    
// Big ugly function that takes as input a string,
// and returns as output its token type.
enum tokenType getType(string input) {
  if (input == "integer" || input == "boolean") {
    return type;
  }
  else if  (input == "true" || input == "false") {
    return booleanvalue;
  }
  else if (input == "and" || input == "or" || input == "not") {
    return booleanop;
  }
  else if (input == "if" || input == "then" || input == "else"
  || input == "print" || input == "program" ||
  input == "function" || input == "return" || input == "begin"
  || input == "end" || input == "end") {
    return keyword;
  }
  else if (isValidNum(input)) {
    return number;
  }
  else {
    if (input.length() > MAX_IDENT_LENGTH) {
      return invalid;
    }
    else {
      if (!isalpha(input.front())) {
        return invalid;
      }
      int i = 1;
      while(i < input.length()) {
        if (!isalnum(input.at(i))) {
          break;
        }
        i++;
      }
      if (i == input.length()) {
        return identifier;
      }
      else {
        return invalid;
      }
    }
  }
}
