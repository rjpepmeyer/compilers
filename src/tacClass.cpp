enum tacOp {add,sub,mul,div,neg,ass};

class TAC {
  private:
    tacOp op;
    std::string arg1;
    std::string arg2;
    std::string res;
  public:
    void setOp(tacOp in){this->op = in};
    void set1(std::string in){this->arg1 = in};
    void set2(std::string in){this->arg2 = in};
    void setRes(std::string in){this->res = in};
    std::string getRes(std::string in){
      switch (op){
        case ass:
          res = arg1;
      }
      return res;
    };
};
