#include <string>
#include <ctype.h>

using namespace std;

// Takes a character as an argument
// Returns TRUE if character matches a self deliminating token.
bool isSelfDeliminator(char c) {
  string selfDeliminators = "+-*/<=(),:{;}";
  for(int i = 0; i < selfDeliminators.length(); i++) {
    if (c == selfDeliminators[i]) return true;
  }
  return false;
}

// Returns string of enum
string toString(enum tokenType input) {
  switch(input) {
    case op:           return "<operator>   "; break;
    case lessthan:     return "<less-than>  "; break;
    case equals:       return "<equals>     "; break;
    case leftparen:    return "<left-paren> "; break;
    case rightparen:   return "<left-paren> "; break;
    case separator:    return "<separator>  "; break;
    case terminator:   return "<terminator> "; break;
    case comma:        return "<comma>      "; break;
    case invalid:      return "<invalid>    "; break;
    case type:         return "<typename>   "; break;
    case booleanvalue: return "<bool-value> "; break;
    case booleanop:    return "<bool-op>    "; break;
    case keyword:      return "<keyword>    "; break;
    case number:       return "<number>     "; break;
    case invalidnum:   return "<invalid-num>"; break;
    case identifier:   return "<identifier> "; break;
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
  else {
    return invalid;
  }
}
    
// Big ugly function that takes as input a token,
// and returns as output a string containing
// the type of the token.

enum tokenType getType(string input) {
  if (input == "integer" || input == "boolean") {
    return op;
  }
  else if  (input == "true" || input == "false") {
    return lessthan;
  }
  else if (input == "and" || input == "or" || input == "not") {
    return equals;
  }
  else if (input == "if" || input == "then" || input == "else"
  || input == "print" || input == "program" ||
  input == "function" || input == "return" || input == "begin"
  || input == "end" || input == "end.") {
    return keyword;
  }
  else if (input.at(0) == '0') {
    if (input.length() == 1) {
      return number;
    }
    else {
      return invalidnum;
    }
  }
  else if (isdigit(input.at(0))) {
    int i = 0;
    while(i < input.length()) {
      if (!isdigit(input.at(i))) {
        break;
      }
      i++;
    }
    if (i == input.length()) {
      return number;
    }
    else {
      return invalid;
    }
  }
  else {
    if (input.length() > 255) {
      return invalidnum;
    }
    else {
      if (!isalpha(input.at(0))) {
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
