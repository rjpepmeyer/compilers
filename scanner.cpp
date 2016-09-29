#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <iomanip>
#include "scanner.hpp"

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
string print(enum tokenType input) {
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
      int i = 0;
      while(i < input.length()) {
        if (!isalpha(input.at(i))) {
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

int main(int argc, char *argv[]) {
  unsigned long line = 1; // line number currently reading from
  string accum = "";      // characters read in of current token so far
  char currentChar;       // the current character being read
  bool isComment = false; // TRUE if scanning a comment
  tokenList * output = 0;
  tokenList * lastOutput = 0;
  token currentToken;
  
  // Opening file
  ifstream inputFile;
  inputFile.open(argv[1]);
  // Scanner loop
  while(1) {
    inputFile.get(currentChar);
    if (!isComment) { // Skip to ELSE if reading a comment
      if (inputFile.eof()) { // End of file -- breaks loop
        break;
      }
      else if (isspace(currentChar)) { // Found white space
        if (accum.length() > 0) { // If full, accum is token
          currentToken.value = accum;
          currentToken.type  = getType(accum);
          currentToken.line  = line;
          // TODO: Logic that adds current token to token list
          cout << currentToken.line << " "
           << print(currentToken.type) << currentToken.value << '\n';
        }
        accum = "";
        if (currentChar == '\n') line++; // increment line count
      }
      else if (isSelfDeliminator(currentChar)) { // Found deliminator
        if (accum.length() > 0) { // If full, accum is token
          currentToken.value = accum;
          currentToken.type  = getType(accum);
          currentToken.line  = line;
          // TODO: Logic that adds current token to token list
          cout << currentToken.line << " "
           << print(currentToken.type) << currentToken.value << '\n';
        }
        accum = "";
        if (currentChar != '{') { // Current char is a token
          currentToken.value = string(1, currentChar);
          currentToken.type  = getType(currentChar);
          currentToken.line  = line;
          // TODO: Logic that adds current token to token list
          cout << currentToken.line << " "
           << print(currentToken.type) << currentToken.value << '\n';
        }
        else { // '{' indicates the beginning of a comment
          isComment = true;
        }
      }
      else { // Finally, the "default" case
        accum += currentChar;
      }
    }
    else { // Reading a comment block
      if (currentChar == '}') isComment = false; // End comment
    }
  }
  // Close file
  inputFile.close();
  return 0;
}
