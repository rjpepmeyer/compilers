#include <string>

using namespace std;

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

void print(token item) {
  cout << item.line << " ";
  cout << toString(item.type);
  if (item.value.length() > 1 || item.type == op) {
    cout << item.value;
  }
  cout << '\n';
}

token make(string val, enum tokenType type, unsigned long line) {
  token output;
  output.value = val;
  output.type = type;
  output.line = line;
  return output;
}
