#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <iomanip>
#include "scanner.hpp"
#include "scanner-utilities.cpp"

using namespace std;

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
           << toString(currentToken.type) << currentToken.value 
           << '\n';
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
           << toString(currentToken.type) << currentToken.value 
           << '\n';
        }
        accum = "";
        if (currentChar != '{') { // Current char is a token
          currentToken.value = string(1, currentChar);
          currentToken.type  = getType(currentChar);
          currentToken.line  = line;
          // TODO: Logic that adds current token to token list
          cout << currentToken.line << " "
           << toString(currentToken.type) << currentToken.value 
           << '\n';
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
