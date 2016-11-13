#include <string>

void pad(int d) {for(int i=0;i<d;i++) {cout<<' ';}}

enum Node_Type {
  n_program, n_formal,  n_def,        n_body,       n_statement, n_print,
  n_return,  n_if,      n_not,        n_fncall,     n_negate,    n_block,
  n_binexp,  n_expr,    n_identifier, n_type,       n_operator,  n_number,
  n_boolean, n_formals, n_defs,       n_statements, n_exprs
};

// Used by semantic actions
int widthOf(Node_Type n) {
  switch(n) {
    case n_program:    return 4; break;
    case n_formal:     return 2; break;
    case n_def:        return 4; break;
    case n_body:       return 1; break;
    case n_statement:  return 1; break;
    case n_print:      return 1; break;
    case n_return:     return 1; break;
    case n_if:         return 3; break;
    case n_not:        return 1; break;
    case n_fncall:     return 2; break;
    case n_negate:     return 1; break;
    case n_block:      return 1; break;
    case n_binexp:     return 3; break;
    default:           return -1; break; // indicates special condition
  }
}

class Node {
  protected:
    std::string name = "Node";
    Node_Type   nt;
  public:
    Node_Type getType() {return nt;}
    void print(int d) {
      pad(d);
      cout << name << '\n';
    }
};

class IdentifierNode;
class BooleanNode;
class NumberNode;
class FormalList;
class DefList;
class BodyNode;
class StatementList;
class PrintStmtNode;
class ReturnStmtNode;
class ExpressionNode;
class ExpressionList;
class SemanticNode;
