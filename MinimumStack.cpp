#include <iostream>
#include <stack>
using namespace std;

class MinStack {
  private:
    stack<pair<int, int>> minSt;
    int minNum;

  public:
    MinStack() {
      minNum = 1e5;
    }

    void addElement(int elem) {
      minNum = !minSt.empty() ? min(minNum, elem) : elem;
      pair<int, int> newElem;
      newElem.first = elem;
      newElem.second = minNum;
      minSt.push(newElem);
    }

    void removeElement() {
      minSt.pop();
      minNum = minSt.top().second;
    }

    int getMin() {
      return minNum;
    }
};

int main() {
  MinStack st;
  st.addElement(4);
  st.addElement(2);
  cout << st.getMin() << endl;
  st.removeElement();
  cout << st.getMin() << endl;
}
