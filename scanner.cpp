#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <iomanip>

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

// Function that takes as input a single character token,
// and returns as output a string containing the type of
// the token.
string getType(char input) {
  if (input == '+' || input == '-' || input == '*' || 
  input == '/') {
    return " <operator>     ";
  }
  else if (input == '<') {
    return " <less-than>     ";
  }
  else if (input == '=') {
    return " <equals>        ";
  }
  else if (input == '(') {
    return " <left-paren>    ";
  }
  else if (input == ')') {
    return " <right-paren>   ";
  }
  else if (input == ':') {
    return " <separator>     ";
  }
  else if (input == ';') {
    return " <terminator>    ";
  }
  else if (input == ',') {
    return " <comma>         ";
  }
  else {
    return " <invalid>       ";
  }
}
    
// Big ugly function that takes as input a token,
// and returns as output a string containing
// the type of the token.

string getType(string input) {
  if (input == "integer" || input == "boolean") {
    return " <typename>     ";
  }
  else if  (input == "true" || input == "false") {
    return " <booleanvalue> ";
  }
  else if (input == "and" || input == "or" || input == "not") {
    return " <boolean-op>   ";
  }
  else if (input == "if" || input == "then" || input == "else"
  || input == "print" || input == "program" ||
  input == "function" || input == "return" || input == "begin"
  || input == "end" || input == "end.") {
    return " <keyword>      ";
  }
  else if (input.at(0) == '0') {
    if (input.length() == 1) {
      return " <number>       ";
    }
    else {
      return " <invalid-num>  ";
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
      return " <number>       ";
    }
    else {
      return " <invalid>      ";
    }
  }
  else {
    if (input.length() > 255) {
      return " <invalid>      ";
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
        return " <identifer>    ";
      }
      else {
        return " <invalid>      ";
      }
    }
  }
}

int main(int argc, char *argv[]) {
  unsigned long line = 1; // line number currently reading from
  string accum = "";      // characters read in of current token so far
  char currentChar;       // the current character being read
  bool isComment = false; // TRUE if scanning a comment
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
          cout << line << getType(accum) << accum << '\n';
        }
        accum = "";
        if (currentChar == '\n') line++; // increment line count
      }
      else if (isSelfDeliminator(currentChar)) { // Found deliminator
        if (accum.length() > 0) { // If full, accum is token
          cout << line << getType(accum) << accum << '\n';
        }
        accum = "";
        if (currentChar != '{') { // Current char is a token
          cout << line << getType(currentChar) << '\n';
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
