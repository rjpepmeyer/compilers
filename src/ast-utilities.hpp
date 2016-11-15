#include <string>

void pad(int d) {for(int i=0;i<d;i++) {cout<<' ';}}

enum Node_Type {
  n_program, n_formal,  n_def,        n_body,       n_statement, n_print,
  n_return,  n_if,      n_not,        n_fncall,     n_negate,    n_block,
  n_binexp,  n_expr,    n_identifier, n_type,       n_operator,  n_number,
  n_boolean, n_formals, n_defs,       n_statements, n_exprs,     n_stop,
  n_invalid
};

bool isStatement(Node_Type n) {
  return (n == n_statement || n == n_print || n == n_return);
}

bool isExpression(Node_Type n) {
  return (n == n_binexp     || n == n_if     || n == n_not     || n == n_fncall
      ||  n == n_identifier || n == n_number || n == n_boolean || n == n_negate 
      ||  n == n_block);
}

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
    virtual Node_Type getType()=0;
    virtual void print(int)=0;
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
