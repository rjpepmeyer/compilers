#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum tokenType {foo, bar};

struct tokenNode {
  string token;
  tokenType type;
  unsigned long line;
  tokenNode* next;
};

int main(int argc, char *argv[]) {
  // Opening file
  ifstream inputFile;
  inputFile.open(argv[1]);
  // Declarations
  unsigned long line = 1;
  tokenNode* tokenStream = 0;
  tokenNode* lastToken = 0;
  string accum = "";
  char currentChar;
  inputFile.get(currentChar);
  // Scanner loop
  while(!inputFile.eof()) {
    cout << currentChar; 
    inputFile.get(currentChar);
  }
  // Close file
  inputFile.close();
  return 0;
}
