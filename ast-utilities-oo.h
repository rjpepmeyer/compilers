#include <string>

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

class Formal_Node : public Node: {
	public:
		void print(int i){
			Node::print(i);
			indentifier.print(i + 1);
			type.print(i + 1);
		}
		
	protected: 
		Identifier_Node     identifier;
		Type_Node           type;
};

class Def_Node : public program_Node {
	public:
		void print(int i){
			Node::print(i);
			identifier.print(i+1);
			for(int x=0;x<formals.length();x++){formals[x].print(i+1);}
			type.print(i+1);
			body.print(i+1);
		}
	protected:
	    std::string       name = "Definition";
	//  Identifier_Node   identifier;
	//  Formal_Node[]     formals;
		Type_Node         type;
	//  Body_Node         body;
};

class Body_Node : public Node {
	public:
		void print(int i){
			Node::print(i);
			for(int x=0;x<statements.length();x++){statements[x].print(i+1);}
		}
	protected:
		std::string       name = "Body";
		Statement_Node[]  statements;
};

class Statement_Node : public Node {
	public:
		void print(int i){
			Node::print(i);
			print.print(i+1);
			returnVal.print(i+1);
		}
	protected:
		std::string       name = "Statement";
		Print_Node        print;
		Return_Node       returnVal;
};

class Print_Node : public Node {
	public:
		void print(int i){
			Node::print(i);
			exprOne.print(i+1);
		}
	protected:
		std::string       name = "Print";
		Expr_Node_Type    exprOne;
};

class Return_Node : public print_Node {
	//ublic:
	//  void print()
	protected:
		std::string       name = "Return";
	//  Expr_Node_Type    exprOne
};

class If_Node : public print_Node {
	public:
		void print(int i){
			Node::print(i);
			exprOne.print(i+1);
			exprTwo.print(i+1);
			exprThree.print(i+1);
		}
	protected:
		std::string       name = "If";
	//  expr_Node_Type    exprOne
		Expr_Node_Type    exprTwo;
		Expr_Node_Type    exprThree;
};

class Not_Node : public print_Node {
	//blic:
	//  void print()
	protected:
		std::string       name = "Not";
	//  Expr_Node_Type    exprOne
}; 

class Function_Call_Node : public Node {
	public:
		void print(int i){
			Node::print(i);
			identifier.print(i+1);
			for(int x=0;x<expresions.length();x++){expressions[x].print(i+1);}
		}
	protected:
		std::string       name = "Function Call";
		Identifier_Node   identifier;
		Expr_Node_Type[]  expresions;
};

class Negate_Node : public print_Node {
	//blic:
	//  void print()
	protected:
		std::string       name = "Negate";
	//  Expr_Node_Type    exprOne
};

class Block_Node : public print_Node {
	//blic:
	//  void print()
	protected:
		std::string       name = "Block";
	//  Expr_Node_Type    exprOne
};

class Binary_Expr_Node : public print_Node {
	public:
		void print(int i){
			Node::print(i);
			exprOne.print(i+1);
			op.print(i+1);
			exprTwo.print(i+1);
		}
	protected:
		std::string       name = "Binary Expression";
	//  Expr_Node_Type    exprOne
		Expr_Node_Type    exprTwo;
		Operator_Node     op;
};

class Expr_Node_Type : public Node {
	protected:
		Node              expression;
};

// Simple nodes
class Identifier_Node : public Node {
	public:
		void setVal(std::string val){
			value = val;
		}
	private:
	    std::string       name = "Identifier";
		std::string       value;
};

class Type_Node : public Node {
	public:
		void setVal(tokenType val){
			value = val;
		}
	private:
	    std::string       name = "Type";
		TokenType         value;
};

class Number_Node : public Node {
	public:
		void setVal(unsigned long val){
			value = val;
		}
	private:
	    std::string       name = "Number";
		unsigned long     value;
};

class Boolean_Node : public Node {
	public:
		void setVal(bool val){
			value = val;
		}
	private:
	    std::string       name = "Boolean";
		bool              value;
};

class Operator_Node : public Node {
	public:
		void setVal(char val){
			value = val;
		}
	private:
	    std::string       name = "Operator";
		char              value;
};

class Program_Node : public Node {
	public:
		void addIdentifier(std::string val){
			identifier = new identifier_Node.setVal(val);
		}
		
		void print(){
			Node::print(0);
			identifier.print(1);
			for(int i=0;i<formals.length();i++){formals[i].print(1);}
			for(int i=0;i<definitions.length();i++){definitions[i].print(1);}
			body.print(1);
		}
	
	protected:
	    std::string       name = "Program";
		Identifier_Node   identifier;
		Formal_Node[]     formals;
		Body_Node         body;
		
	private:
		Def_Node[]        definitions;
};
