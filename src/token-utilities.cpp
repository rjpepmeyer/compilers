#include <string>

using namespace std;

// Adds a tokenList node to a token list
void add(tokenList * &root, tokenList * &current, token item) {
  tokenList * newNode = new tokenList;
  newNode->item = item;
  newNode->next = NULL;
  if (current == NULL) {
    root = newNode;
    current = newNode;
  }
  else {
    current->next = newNode;
    current = current->next;
  }
}

// Prints a token as a single line output
void print(token item) {
  cout << item.line << " ";
  cout << toString(item.type);
  if (item.value.length() > 1 || item.type == op || item.type 
  == number) {
    cout << item.value;
  }
  cout << '\n';
}

// Sets the values of a token
token make(string val, enum tokenType type, unsigned long line) {
  token output;
  output.value = val;
  output.type = type;
  output.line = line;
  return output;
}

token make(string val, enum tokenType type) {
  token output;
  output.value = val;
  output.type = type;
  output.line = 0;
  return output;
}

token make(enum tokenType type) {
  token output;
  output.value = "";
  output.type = type;
  output.line = 0;
  return output;
}
