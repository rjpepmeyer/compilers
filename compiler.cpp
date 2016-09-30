#include <iostream>
#include <string>
#include "scanner.hpp"
#include "scanner-utilities.cpp"
#include "token-utilities.cpp"
#include "scanner.cpp"

using namespace std;

int main(int argc, char *argv[]) {
  // Run scanner on input file
  tokenList * streamOfTokens = scanner(argv[1]);
  // Print out results of scanner
  tokenList * i = streamOfTokens;
  while (i != NULL) {
    print(i->item);
    i = i->next;
  }
  //TODO: Free memory from stream of tokens
  return 0;
}
