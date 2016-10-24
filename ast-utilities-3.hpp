#include <string>

void pad(int d) {for(int i=0;i<d;i++) {cout<<' ';}}

class Node {
  protected:
    std::string name = "Node";
  public:
    void print(int d) {
      pad(d);
      cout << name << '\n';
    }
};

class FormalList;
class DefList;
class BodyNode;
class StatementList;
class PrintStmtNode;
class ReturnStmtNode;
class ExpressionNode;
class ExpressionList;
