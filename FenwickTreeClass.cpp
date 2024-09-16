#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
  private:
    vector<int> tree;
    int size;

  public:
    FenwickTree(vector<int> arr) : tree(arr.size() + 1){
      size = arr.size() + 1;
      for(int i = 1; i < size; ++i) {
        updateTree(i - 1, arr[i - 1]);
      }
    }

    void updateTree(int index, int val) {
      ++index;
      while(index < size) {
        tree[index] += val;
        index += (index & -index);
      }
    }

    int getSum(int index) {
      ++index;
      int sum = 0;
      while(index > 0) {
        sum += tree[index];
        index -= (index & -index);
      }
      return sum;
    }

    void printTree() {
      for(int i : tree) {
        cout << i << " ";
      }
      cout << endl;
    }
};

int main() {
  vector<int> arr = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
  FenwickTree tree(arr);
  tree.printTree();
  cout << tree.getSum(12) << endl;
}
