#include <iostream>
#include <fstream>
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
          cout << line << " <UNKNOWN> " << accum << '\n';
        }
        accum = "";
        if (currentChar == '\n') line++; // increment line count 
      }
      else if (isSelfDeliminator(currentChar)) { // Found deliminator
        if (accum.length() > 0) { // If full, accum is token
          cout << line << " <UNKNOWN> " << accum << '\n';
        }
        accum = "";
        if (currentChar != '{') { // Current char is a token
          cout << line << " <UNKNOWN> " << currentChar << '\n';
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
