#include <string>

// Simple nodes
struct identifier_ast {std::string   value;};
struct type_ast       {tokenType     value;};
struct number_ast     {unsigned long value;};
struct boolean_ast    {bool          value;};
struct operator_ast   {char          value;};

struct formal_ast  {
  identifier_ast identifier;
  type_ast       type;
};

struct if-ast {
  leftChild      then_ast;// then expression node
  rightChild     else_ast;// else expression node
};

struct then-ast {
    leftChild    expr_ast;//expr with boolean result
    rightChild   expr_ast;//expr to perform if L-child is true
};

struct else-ast {
    leftChild    expr_ast;//expr with boolean result
    rightChild   expr_ast;//expr to perform if L-child is false
};

// Struct Prototype
struct /*Name*/ {
  //(Values)*
};

// Binary Prototype
struct /*name*/_ast {
    leftChild    /*node*/_ast;
    rightChild   /*node*/_ast;
};
