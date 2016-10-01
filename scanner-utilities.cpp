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
  if (input.length() > 1 && input.front() == '0') {
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
    case identifier:   return "<identifier> "; break;
    case punctuation:  return "<punctuation>"; break;
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
