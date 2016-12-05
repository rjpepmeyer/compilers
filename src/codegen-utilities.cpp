class LineManager {
  protected:
    unsigned int num = 0;
  public:
    int getNum() {
      num++;
      return num - 1;
    }
}
