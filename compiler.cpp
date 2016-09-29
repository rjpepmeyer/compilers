#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <iomanip>
#include "scanner.hpp"
#include "scanner-utilities.cpp"
#include "token-utilities.cpp"
#include "scanner.cpp"

using namespace std;

int main(int argc, char *argv[]) {
  tokenList * streamOfTokens = scanner(argv[1]);
  while (streamOfTokens != NULL) {
    print(streamOfTokens->item);
    streamOfTokens = streamOfTokens->next;
  }
  return 0;
}
