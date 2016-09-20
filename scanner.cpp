#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum tokenType {foo, bar}; //Needs filled out

/* Node for list of tokens--probably unnecessary
struct tokenNode {
  string token;
  tokenType type;
  unsigned long line;
  tokenNode* next;
};
*/

int main(int argc, char *argv[]) {
  // Declarations
  unsigned long line = 1;
  string accum = "";
  char currentChar;
  // Opening file
  ifstream inputFile;
  inputFile.open(argv[1]);
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
