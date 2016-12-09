enum tacOp {t_add,t_sub,t_mul,t_div,t_neg,t_ass};

using namespace std;

class TAC {
  private:
    tacOp op;
    int arg1;
    int arg2;
    int res;
  public:
    void setOp  (tacOp in) {op   = in;}
    void set1   (int in)   {arg1 = in;}
    void set2   (int in)   {arg2 = in;}
    void setRes (int in)   {res  = in;}
    TAC(tacOp o, int a1, int a2, int r) {
      setOp(o);
      set1(a1);
      set2(a2);
      setRes(r);
    }
    TAC() {
      TAC(t_ass,0,0,0);
    }
    tacOp getOp()   {return op;}
    int   get1()    {return arg1;}
    int   get2()    {return arg2;}
    int   getRes()  {return res;}
};

class TACs {
  private:
    TAC    value;
    TACs * next = NULL;
  public:
    void setValue(TAC   v) {value = v;}
    void setNext (TACs *n) {next  = n;}
    TACs(TAC v, TACs *n) {
      setValue(v);
      setNext(n);
    }
    void add(TAC v) {
      if (next == NULL) {
        next = new TACs(v, NULL);
      }
      else {
        next->add(v);
      }
    }
    TAC getValue() {return value;}
    TACs * getNext() {return next;}
    void increment() {
      if (next != NULL) {
        value = next->getValue();
        next  = next->getNext();
      }
    }
};

