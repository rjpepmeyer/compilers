#include <iostream>
#include <string>

using namespace std;

enum tokenType {foo, bar};

struct tokenNode {
  string token;
  tokenType type;
  unsigned long line;
  tokenNode* next;
};

int main() {
  unsigned long line = 1;
  tokenNode* tokenStream = 0;
  tokenNode* lastToken = 0;
  string accum = "";
  
  // Open file here
  
  while(0) {
    // Scanner process
  }
  
  // Close file here
  
  return 0;
}
