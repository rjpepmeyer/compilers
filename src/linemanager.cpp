class LineManager {
  protected:
    unsigned int num = 0;
  public:
    int getNum() {
      // Gives out the next available line number
      num++;
      return num - 1;
    }
    bool reqNum(int val) {
      // Returns true if a line number is available to be reserved, and reserves it
      return true;
    }
}
