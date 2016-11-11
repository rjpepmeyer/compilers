#include <string>
#include <iostream>
#include <sstream>
#include "ast-utilities.hpp"

/**************************************
           BASIC NODE TYPES
**************************************/

class IdentifierNode : public Node {
  protected:
    std::string name = "Identifier";
    std::string value;
  public:
    IdentifierNode() {
      value = "";
    }
    IdentifierNode(std::string val) {
      value = val;
    }
    void print(int d) {
      pad(d);
      cout << name <<  ": " << value << '\n';
    }
};

class TypeNode : public Node {
  protected:
    std::string name = "Type";
    std::string value;
  public:
    TypeNode() {
      value = "";
    }
    TypeNode(tokenType val) {
      if (val == booleanvalue) {
        value = "boolean";
      }
      else if (val == number) {
        value = "number";
      }
    }
    void print(int d) {
      pad(d);
      cout << name << ": " << value << '\n';
    }
};

class BinaryOpNode : public Node {
  protected:
    std::string name = "Binary Operator";
    char        value;
  public:
    BinaryOpNode(char val) {
      value = val;
    }
    BinaryOpNode() {}
    void print(int d) {
      pad(d);
      cout << name << ": " << value << '\n';
    }
};

class NumberNode : public Node {
  protected:
    std::string  name = "Number";
    unsigned int value;
  public:
    NumberNode(std::string val) {
      istringstream(val) >> value;
    }
    void print(int d) {
      pad(d);
      cout << name << ": " << value << '\n';
    }
};

class BooleanNode : public Node {
  protected:
    std::string name = "Boolean";
    bool        value;
  public:
    BooleanNode(std::string val) {
      if (val.front() == 't') {
        value = true;
      }
      else {
        value = false;
      }
    }
    void print(int d) {
      pad(d);
      cout << name << ": ";
      if (value) cout << "true"; else cout << "false";
      cout << '\n';
    }
};

/***************************************
            Complex nodes!
***************************************/

class ProgramNode : public Node {
  protected:
    std::string     name = "Program";
    IdentifierNode  value;
    FormalList     *formals;
    DefList        *defs;
    BodyNode       *body;
  public:
    void setValue(IdentifierNode *i) {value = *i;};
    void setFormals(FormalList *i) {formals = i;};
    void setDefs(DefList *i) {defs = i;};
    void setBody(BodyNode *i) {body = i;};
    ProgramNode(IdentifierNode *v, FormalList *f, DefList *d, BodyNode *b){
      setValue(v);
      setFormals(f);
      setDefs(d);
      setBody(b);
    }
    void print(int);
};

class FormalParamNode : public Node {
  protected:
    std::string    name = "Formal Parameter";
    IdentifierNode value;
    TypeNode       type;
  public:
    void setValue(IdentifierNode i) {value = i;}
    void setType(TypeNode t) {type = t;}
    FormalParamNode(IdentifierNode i, TypeNode t) {
      setValue(i);
      setType(t);
    }
    void print(int d) {
      pad(d);
      cout << name << '\n';
      value.print(d+1);
      type.print(d+1);
    }
};

class FormalList : public Node {
  protected:
    std::string      name = "List of formal parameters";
    FormalParamNode *value;
    FormalList      *next;
  public:
    FormalList(FormalParamNode *f) {
      value = f;
    }
    void addFormal(FormalParamNode f) {
      if (next == NULL) {
        next = new FormalList(&f);
      }
      else {
        (*next).addFormal(f);
      }
    }
    void print(int d) {
      if (value != NULL) {(*value).print(d);}
      if (next != NULL) {(*next).print(d);}
    }
};

class DefNode : public Node {
  protected:
    std::string     name = "Definition";
    IdentifierNode  value;
    FormalList     *formals;
    TypeNode        type;
    BodyNode       *body;
  public:
    void setValue(IdentifierNode *v) {value = *v;};
    void setFormals(FormalList *f) {formals = f;};
    void setType(TypeNode *t) {type = *t;};
    void setBody(BodyNode *b) {body = b;};
    DefNode(IdentifierNode *v, FormalList *f, TypeNode *t, BodyNode *b) {
      setValue(v);
      setFormals(f);
      setType(t);
      setBody(b);
    }
    void print(int);
};

class DefList : public Node {
  protected:
    std::string  name = "Definitions List";
    DefNode     *value;
    DefList     *next;
  public:
    DefList(DefNode *d) {
      value = d;
    }
    void addDef(DefNode d) {
      if (next == NULL) {
        next = new DefList(&d);
      }
      else {
        (*next).addDef(d);
      }
    }
    void print(int d) {
      if (value != NULL) {(*value).print(d);}
      if (next  != NULL) { (*next).print(d);}
    }
};

class BodyNode : public Node {
  protected:
    std::string    name = "Body";
    StatementList *value;
  public:
    BodyNode(StatementList *s) {
      value = s;
    }
    void print(int);
};

class StatementNode : public Node {
  protected:
    std::string      name;
    ExpressionNode * value;
  public:
    void setValue(ExpressionNode *e) {value = e;}
    virtual void print(int) =0;
};

class PrintStmtNode : public StatementNode {
  protected:
    std::string     name = "Print Statement";
    ExpressionNode *value;
  public:
    void setValue(ExpressionNode *e) {value = e;}
    PrintStmtNode (ExpressionNode *e) {setValue(e);}
    void print(int);
};

class ReturnStmtNode : public StatementNode {
  protected:
    std::string     name = "Return Statement";
    ExpressionNode *value;
  public:
    void setValue(ExpressionNode *e) {value = e;}
    ReturnStmtNode (ExpressionNode *e) {setValue(e);}
    void print(int);
};

class StatementList : public Node {
  protected:
    std::string    name = "Statement List";
    StatementNode *value;
    StatementList *next;
  public:
    StatementList(StatementNode *s) {value = s;}
    void addStatement(StatementNode *s) {
      if (next == NULL) {
        next = new StatementList(s);
      }
      else {
        (*next).addStatement(s);
      }
    }
    void print(int d) {
      if (value != NULL) {(*value).print(d);}
      if (next  != NULL) { (*next).print(d);}
    }
};

class IfExprNode : public Node {
  protected:
    std::string     name = "If Expression";
    ExpressionNode *test;
    ExpressionNode *thenClause;
    ExpressionNode *elseClause;
  public:
    void setTest(ExpressionNode *e) {test = e;}
    void setThen(ExpressionNode *e) {thenClause = e;}
    void setElse(ExpressionNode *e) {elseClause = e;}
    IfExprNode (ExpressionNode *t, ExpressionNode *th, ExpressionNode *e) {
      setTest(t);
      setThen(th);
      setElse(e);
    }
    void print(int);
};

class NotExprNode : public Node {
  protected:
    std::string     name = "Not Expression";
    ExpressionNode *value;
  public:
    void setValue(ExpressionNode *e) {value = e;}
    NotExprNode (ExpressionNode *e) {setValue(e);}
    void print(int);
};

class FunctionCallNode : public Node {
  protected:
    std::string     name = "Function Call";
    IdentifierNode  functionName;
    ExpressionList *functionBody;
  public:
    void setName(IdentifierNode *i) {functionName = *i;}
    void setBody(ExpressionList *e) {functionBody = e;}
    FunctionCallNode(IdentifierNode *i, ExpressionList *e) {
      setName(i);
      setBody(e);
    }
    void print(int);
};

class NegateExprNode : public Node {
  protected:
    std::string     name = "Negate Expression";
    ExpressionNode *value;
  public:
    void setValue(ExpressionNode *e) {value = e;}
    NegateExprNode(ExpressionNode *e) {setValue(e);}
    void print(int);
};

class BlockExprNode : public Node {
  protected:
    std::string     name = "Block Expression";
    ExpressionNode *value;
  public:
    void setValue(ExpressionNode *e) {value = e;}
    BlockExprNode(ExpressionNode *e) {setValue(e);}
    void print(int);
};

class BinaryExprNode : public Node {
  protected:
    std::string     name = "Binary Expression";
    ExpressionNode *left;
    BinaryOpNode    op;
    ExpressionNode *right;
  public:
    void setLeft (ExpressionNode *e) {left  = e;}
    void setOp   (BinaryOpNode *o)   {op    = *o;}
    void setRight(ExpressionNode *e) {right = e;}
    BinaryExprNode(ExpressionNode *l, BinaryOpNode *o, ExpressionNode *r) {
      setLeft(l);
      setOp(o);
      setRight(r);
    }
    void print(int);
};

/**************************************
           Expression node!
         (this one's a doozy)
**************************************/

enum ExpressionType {binaryexpr, ifexpr, notexpr, functioncall,
identifierexpr, numberexpr, booleanexpr, negateexpr, blockexpr};

class ExpressionNode : public Node {
  protected:
    std::string     name = "Expression";
    ExpressionType  type;
    void           *value;
  public:
    void setValue(BinaryExprNode *b) {
      type = binaryexpr;
      value = b;
    }
    void setValue(IfExprNode *i) {
      type = ifexpr;
      value = i;
    }
    void setValue(NotExprNode *n) {
      type = notexpr;
      value = n;
    }
    void setValue(FunctionCallNode *f) {
      type = functioncall;
      value = f;
    }
    void setValue(IdentifierNode *i) {
      type = identifierexpr;
      value = i;
    }
    void setValue(NumberNode *n) {
      type = numberexpr;
      value = n;
    }
    void setValue(BooleanNode *b) {
      type = booleanexpr;
      value = b;
    }
    void setValue(NegateExprNode *n) {
      type = negateexpr;
      value = n;
    }
    void setValue(BlockExprNode *b) {
      type = blockexpr;
      value = b;
    }
    ExpressionNode(BinaryExprNode   *e) {setValue(e);}
    ExpressionNode(IfExprNode       *e) {setValue(e);}
    ExpressionNode(NotExprNode      *e) {setValue(e);}
    ExpressionNode(FunctionCallNode *e) {setValue(e);}
    ExpressionNode(IdentifierNode   *e) {setValue(e);}
    ExpressionNode(NumberNode       *e) {setValue(e);}
    ExpressionNode(BooleanNode      *e) {setValue(e);}
    ExpressionNode(NegateExprNode   *e) {setValue(e);}
    ExpressionNode(BlockExprNode    *e) {setValue(e);}
    void print(int d) {
      switch(type) {
        case binaryexpr:
          (*static_cast<BinaryExprNode*>(value)).print(d);break;
        case ifexpr:
          (*static_cast<IfExprNode*>(value)).print(d);break;
        case notexpr:
          (*static_cast<NotExprNode*>(value)).print(d);break;
        case functioncall:
          (*static_cast<FunctionCallNode*>(value)).print(d);break;
        case identifierexpr:
          (*static_cast<IdentifierNode*>(value)).print(d);break;
        case numberexpr:
          (*static_cast<NumberNode*>(value)).print(d);break;
        case booleanexpr:
          (*static_cast<BooleanNode*>(value)).print(d);break;
        case negateexpr:
          (*static_cast<NegateExprNode*>(value)).print(d);break;
        case blockexpr:
          (*static_cast<BlockExprNode*>(value)).print(d);break;
        default: break;
      }
    }
};

class ExpressionList : public Node {
  protected:
    std::string     name = "Expression List";
    ExpressionNode *value;
    ExpressionList *next;
  public:
    ExpressionList(ExpressionNode *e) {
      value = e;
    }
    void addExpression(ExpressionNode e) {
      if (next == NULL) {
        next = new ExpressionList(&e);
      }
      else {
        (*next).addExpression(e);
      }
    }
    void print(int d) {
      if (value != NULL) {(*value).print(d);}
      if (next  != NULL) { (*next).print(d);}
    }
};

/**************************************
Print functions that have to be defined
down here to avoid forward declarations
**************************************/

void BinaryExprNode::print(int d) {
  pad(d);
  cout << name << '\n';
  (*left ).print(d+1);
  op.print(d+1);
  (*right).print(d+1);
}

void BlockExprNode::print(int d) {
  pad(d);
  cout << name << '\n';
  (*value).print(d+1);
}

void NegateExprNode::print(int d) {
  pad(d);
  cout << name << '\n';
  (*value).print(d+1);
}

void FunctionCallNode::print(int d) {
  pad(d);
  cout << name << '\n';
  functionName.print(d+1);
  (*functionBody).print(d+1);
}

void NotExprNode::print(int d) {
  pad(d);
  cout << name << '\n';
  (*value).print(d+1);
}

void IfExprNode::print(int d) {
  pad(d);
  cout << name << '\n';
  (*test).print(d+1);
  (*thenClause).print(d+1);
  (*elseClause).print(d+1);
}

void ReturnStmtNode::print(int d) {
  pad(d);
  cout << name << '\n';
  (*value).print(d+1);
}

void PrintStmtNode::print(int d) {
  pad(d);
  cout << name << '\n';
  (*value).print(d+1);
}

void BodyNode::print(int d) {
  pad(d);
  cout << name << '\n';
  (*value).print(d+1);
}

void DefNode::print(int d) {
  pad(d);
  cout << name << '\n';
  value.print(d+1);
  if (formals != NULL) {(*formals).print(d+1);}
  type.print(d+1);
  (*body).print(d+1);
}

void ProgramNode::print(int d) {
  pad(d);
  cout << name << '\n';
  if (formals != NULL) {(*formals).print(d+1);}
  if (defs != NULL) {(*defs).print(d+1);}
  (*body).print(d+1);
}

/**************************************
            Semantic stack
**************************************/

enum SType {sprogram, sformal, sdef, sbody, sstatement, sprint, sreturn, sif,
  snot, sfncall, snegate, sblock, sbinexp, sexpr, sidentifier, stype,
  soperator, snumber, sboolean, sformals, sdefs, sstatements, sexprs};

class SemanticObject {
  protected:
    SType  type;
    void * item;
  public:
    SemanticObject(ProgramNode      * p) {type = sprogram;    item = p;}
    SemanticObject(FormalParamNode  * f) {type = sformal;     item = f;}
    SemanticObject(DefNode          * d) {type = sdef;        item = d;}
    SemanticObject(BodyNode         * b) {type = sbody;       item = b;}
    SemanticObject(StatementNode    * s) {type = sstatement;  item = s;}
    SemanticObject(PrintStmtNode    * p) {type = sprint;      item = p;}
    SemanticObject(ReturnStmtNode   * r) {type = sreturn;     item = r;}
    SemanticObject(IfExprNode       * i) {type = sif;         item = i;}
    SemanticObject(NotExprNode      * n) {type = snot;        item = n;}
    SemanticObject(FunctionCallNode * f) {type = sfncall;     item = f;}
    SemanticObject(NegateExprNode   * n) {type = snegate;     item = n;}
    SemanticObject(BlockExprNode    * b) {type = sblock;      item = b;}
    SemanticObject(BinaryExprNode   * b) {type = sbinexp;     item = b;}
    SemanticObject(ExpressionNode   * e) {type = sexpr;       item = e;}
    SemanticObject(IdentifierNode   * i) {type = sidentifier; item = i;}
    SemanticObject(TypeNode         * t) {type = stype;       item = t;}
    SemanticObject(BinaryOpNode     * o) {type = soperator;   item = o;}
    SemanticObject(NumberNode       * n) {type = snumber;     item = n;}
    SemanticObject(BooleanNode      * b) {type = sboolean;    item = b;}
    SemanticObject(FormalList       * l) {type = sformals;    item = l;}
    SemanticObject(DefList          * l) {type = sdefs;       item = l;}
    SemanticObject(StatementList    * l) {type = sstatements; item = l;}
    SemanticObject(ExpressionList   * l) {type = sexprs;      item = l;}
    SemanticObject() {type = sprogram; item = NULL;}
    SType  getType() {return type;}
    void * getPtr()  {return item;}
};

class SemanticStack {
  protected:
    SemanticNode * item;
  public:
    void push(SemanticObject i);
    SemanticObject pop();
    SType  peekType();
    void * peekPtr();
};

class SemanticNode {
  protected:
    SemanticObject   value;
    SemanticNode   * next;
  public:
    SemanticNode(SemanticObject o, SemanticNode * p) {
      value = o;
      next  = p;
    }
    SemanticObject getValue() {
      return value;
    }
    SemanticNode * getNext() {
      return next;
    }
};

SType SemanticStack::peekType() {
  return (*item).getValue().getType();
}

void * SemanticStack::peekPtr() {
  return (*item).getValue().getPtr();
}


void SemanticStack::push(SemanticObject i) {
  item = new SemanticNode(i, item);
}

SemanticObject SemanticStack::pop() {
  SemanticNode * copy = item;
  SemanticObject value = (*item).getValue();
}

/**************************************
           Semantic actions
**************************************/


