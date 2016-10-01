#include <iostream>
#include <fstream>
#include <string>

using namespace std;

tokenList *  scanner(char *inputFileName) {
  unsigned long line = 1; // line number currently reading from
  string accum = "";      // characters read in of current token so far
  char currentChar;       // the current character being read
  bool isComment = false; // TRUE if scanning a comment
  tokenList *outputRoot = NULL;
  tokenList *outputCurrent = NULL;
  token currentToken;
  
  // Opening file
  ifstream inputFile;
  inputFile.open(inputFileName);
  // Scanner loop
  while(1) {
    inputFile.get(currentChar);
    if (!isComment) { // Skip to ELSE if reading a comment
      if (inputFile.eof() || isspace(currentChar)) {
        if (accum.length() > 0) { // If full, accum is token
          currentToken = make(accum, getType(accum), line);
          add(outputRoot, outputCurrent, currentToken);
        }
        if (inputFile.eof()) break;
        accum = "";
        if (currentChar == '\n') line++; // increment line count
      }
      else if (isSelfDeliminator(currentChar)) { // Found deliminator
        if (accum.length() > 0) { // If full, accum is token
          currentToken = make(accum, getType(accum), line);
          add(outputRoot, outputCurrent, currentToken);
        }
        accum = "";
        if (currentChar != '{') { // Current char is a token
          currentToken = make(string(1, currentChar), 
          getType(currentChar), line);
          add(outputRoot, outputCurrent, currentToken);
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
  return outputRoot;
}
