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
  return 0;
}
