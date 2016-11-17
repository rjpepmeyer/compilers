#include <string>
#include <iostream>
#include <sstream>

/**************************************
            Semantic stack
**************************************/

enum SType {sprogram, sformal, sdef, sbody, sstatement, sprint, sreturn, sif,
  snot, sfncall, snegate, sblock, sbinexp, sexpr, sidentifier, stype,
  soperator, snumber, sboolean, sformals, sdefs, sstatements, sexprs};

class SemanticStack {
  protected:
    SemanticNode * item;
  public:
    SemanticStack() {item = NULL;}
    void push(Node * i);
    Node * pop();
    Node * peek();
};

class SemanticNode {
  protected:
    Node           * value;
    SemanticNode   * next;
  public:
    SemanticNode(Node * n, SemanticNode * p) {
      value = n;
      next  = p;
    }
    Node * getValue() {
      return value;
    }
    SemanticNode * getNext() {
      return next;
    }
};

void SemanticStack::push(Node * i) {
  item = new SemanticNode(i, item);
}

Node * SemanticStack::pop() {
  Node * n;
  if (item != NULL) {
    n = (*item).getValue();
    // TODO: fix memory leak
    item = (*item).getNext();
    return n;
  }
  else {
    return new InvalidNode();
  }
}

Node * SemanticStack::peek() {
  if (item != NULL) {
    return item->getValue();
  }
  else {
    return new InvalidNode();
  }
}
