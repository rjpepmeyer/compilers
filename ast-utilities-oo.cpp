#include <string>
#include "ast-utilities-oo.h"
#include <iostream>

// Base node
class Node {
	//abstract class prototype
	public:
		void print(int i){
			for(int x = i*3;i>0;i--){
				cout << " ";
			}
		cout << this->name << '\n';
		}
	protected:
		std::string       name = "Generic Node, this should never be seen";
};

class xNode : public Node, public Expr_Node_Type, public Identifier_Node, 
	public Type_Node, public Number_Node, public Boolean_Node, 
	public Operator_Node, public Formal_Node, public Function_Call_Node, 
	public Print_Node, public Return_Node, public Statement_Node, 
	public Body_Node, public If_Node, public Not_Node, public Negate_Node,
	public Block_Node, public Binary_Expression_Node, public Def_Node {
	public:
		bool isVoid(){
			return true;
		}
};

class Expr_Node_Type : public Node {
	public:
		void print(int i){
			Node::print(i);
			this->next.print(i);
		}
	protected:
		Node              expression;
		Node		  next;
};

/*****************
***Simple Nodes***
*****************/

class Identifier_Node : public Node {
	public:
		void setVal(std::string val){
			this->value = val;
		}
	private:
		std::string       name = "Identifier";
		std::string       value;
};

class Type_Node : public Node {
	public:
		Type_Node(tokenType val){
			setVal(val);
		}
		void setVal(tokenType val){
			this->value = val;
		}
	private:
		std::string       name = "Type";
		tokenType         value;
};

class Number_Node : public Node {
	public:
		void setVal(unsigned long val){
			this->value = val;
		}
	private:
		std::string       name = "Number";
		unsigned long     value;
};

class Boolean_Node : public Node {
	public:
		void setVal(bool val){
			this->value = val;
		}
	private:
		std::string       name = "Boolean";
		bool              value;
};

class Operator_Node : public Node {
	public:
		void setVal(char val){
			this->value = val;
		}
	private:
		std::string       name = "Operator";
		char              value;
};

/******************
***Complex Nodes***
******************/

class Formal_Node : public Node {
	public:
		Formal_Node(std::string id, tokenType type){
			if(!this->identifier.isVoid()){
				this->identifier = 
					new Identifier_Node(id);
				this->type = new Type_Node(type);
			} else {
			   this->next = 
			      new Formal_Node(id,type);
			}
		}
		void print(int i){
			Node::print(i);
			this->identifier.print(i + 1);
			this->type.print(i + 1);
			this->next->print(i);
		}	
	protected: 
		Identifier_Node     identifier = new xNode;
		Type_Node           type = new xNode;
		Formal_Node         *next = new xNode;
};

class Function_Call_Node : public Node {
	public:
		void print(int i){
			Node::print(i);
			this->identifier.print(i+1);
			this->expression.print(i+1);
		}
	protected:
		std::string       name = "Function Call";
		Identifier_Node   identifier;
		Expr_Node_Type    expression;
};

class Print_Node : public Node {
	public:
		void print(int i){
			Node::print(i);
			this->exprOne.print(i+1);
		}
	protected:
		std::string       name = "Print";
		Expr_Node_Type    exprOne;
};

class Return_Node : public Print_Node {
	//ublic:
	//  void print()
	protected:
		std::string       name = "Return";
	//  Expr_Node_Type    exprOne
};

class Statement_Node : public Node {
	public:
		void print(int i){
			Node::print(i);
			this->printVal.print(i+1);
			this->returnVal.print(i+1);
			this->next->print(i);
		}
	protected:
		std::string       name = "Statement";
		Print_Node        printVal;
		Return_Node       returnVal;
		Statement_Node    *next;
};

class Body_Node : public Node {
	public:
		void print(int i){
			Node::print(i);
			this->statement.print(i+1);
		}
	protected:
		std::string       name = "Body";
		Statement_Node    statement;
};

class If_Node : public Print_Node {
	public:
		void print(int i){
			Node::print(i);
			this->exprOne.print(i+1);
			this->exprTwo.print(i+1);
			this->exprThree.print(i+1);
		}
	protected:
		std::string       name = "If";
	//  	expr_Node_Type    exprOne
		Expr_Node_Type    exprTwo;
		Expr_Node_Type    exprThree;
};

class Not_Node : public Print_Node {
	//blic:
	//  	void print()
	protected:
		std::string       name = "Not";
	//  	Expr_Node_Type    exprOne
}; 

class Negate_Node : public Print_Node {
	//blic:
	//  	void print()
	protected:
		std::string       name = "Negate";
	//  	Expr_Node_Type    exprOne
};

class Block_Node : public Print_Node {
	//blic:
	//  	void print()
	protected:
		std::string       name = "Block";
	// 	Expr_Node_Type    exprOne
};

class Binary_Expr_Node : public Print_Node {
	public:
		void print(int i){
			Node::print(i);
			this->exprOne.print(i+1);
			this->op.print(i+1);
			this->exprTwo.print(i+1);
		}
	protected:
		std::string       name = "Binary Expression";
	//  	Expr_Node_Type    exprOne
		Expr_Node_Type    exprTwo;
		Operator_Node     op;
};

class Def_Node : public Node {
	public:
		void print(int i){
			Node::print(i);
			this->identifier.print(i+1);
			this->formal.print(i+1);
			this->type.print(i+1);
			this->body.print(i+1);
			this->next->print(i);
		}
	protected:
	    std::string       name = "Definition";
	    Identifier_Node   identifier;
	    Formal_Node       formal;
	    Type_Node         type;
	    Body_Node         body;
	    Def_Node	      *next;
};

class Program_Node : public Node {
	public:
		void addFormal(std::string id, tokenType type){
			this->formals = new Formal_Node(id,type);
		}

		void addIdentifier(std::string val){
			this->identifier = new Identifier_Node;
			this->identifier.setVal(val);
		}
		
		void print(){
			Node::print(0);
			this->identifier.print(1);
			this->formals.print(1);
			this->definitions.print(1);
			this->body.print(1);
		}

		
	
	protected:
	    std::string       name = "Program";
		Identifier_Node   identifier;
		Formal_Node       formals;
		Body_Node         body;
		
	private:
		Def_Node          definitions;
};
