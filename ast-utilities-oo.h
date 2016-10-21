#include <string>

// Base node
class Node {
	//abstract class prototype
};

class program_Node: public Node {
	public string          identifier;
	public body            Node;
	public definitions[]   def_Node;
    public formals[]	   formal_Node;
};

class def_Node: public program_Node {
	//it's all the same!
}


// Simple nodes
class identifier_ast {std::string   value;};
class type_ast       {tokenType     value;};
class number_ast     {unsigned long value;};
class boolean_ast    {bool          value;};
class operator_ast   {char          value;};

class formal_Node: public_Node {
  identifier_ast identifier;
  type_ast       type;
};

class if_ast {
  leftChild      then_ast;// then expression node
  rightChild     else_ast;// else expression node
};

class then_ast {
    leftChild    expr_ast;//expr with boolean result
    rightChild   expr_ast;//expr to perform if L-child is true
};

class else-ast {
    leftChild    expr_ast;//expr with boolean result
    rightChild   expr_ast;//expr to perform if L-child is false
};

// class Prototype
class /*Name*/ {
  //(Values)*
};

// Binary Prototype
class /*name*/_ast {
    leftChild    /*node*/_ast;
    rightChild   /*node*/_ast;
};
