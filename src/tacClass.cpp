enum tacOp {add,sub,mul,div,neg,ass};

using namespace std;

class TAC {
  private:
    tacOp op;
    string arg1;
    string arg2;
    string res;
  public:
    void setOp(tacOp in){this->op = in};
    void set1(string in){this->arg1 = in};
    void set2(string in){this->arg2 = in};
    void setRes(string in){this->res = in};
    string getRes(string in){
      switch (op){
        case ass:
          res = arg1;
      }
      return res;
    };
};
