#include <iostream>
#include <vector>
using namespace std;

// Find the Greatest Common Divisor for every range query in an array

class GCDSegmentTree {
  private:
    vector<int> segmentTree;
    int arrSize;

    int euclidean(int a, int b) {
      if(b == 0) return a;
      return euclidean(b, a % b);
    }

  public:
    GCDSegmentTree(vector<int> arr) : segmentTree(2 * arr.size()){
      for(int i = 0; i < arr.size(); ++i) {
        segmentTree[segmentTree.size() - 1 - i] = arr[arr.size() - 1 - i];
      }
      for(int i = arr.size() - 1; i > 0; --i) {
        segmentTree[i] = euclidean(segmentTree[2 * i], segmentTree[2 * i + 1]);
      }
      arrSize = arr.size();
    }

    void updateTree(int index, int val) {
      index += segmentTree.size();
      segmentTree[index] = val;

      index /= 2;

      while(index > 0) {
        segmentTree[index] = euclidean(segmentTree[2 * index], segmentTree[2 *                                   index + 1]);
        index /= 2;
      }
    }

    // [From, to)
    int gcd(int from, int to) {
      from += arrSize;
      to += arrSize;
      int gcd = segmentTree[from];

      while(from < to) {
        if(from % 2) {
          gcd = euclidean(gcd, segmentTree[from]);
          from++;
        }
        if(to % 2) {
          --to;
          gcd = euclidean(gcd, segmentTree[to]);
        }
        from /= 2;
        to /= 2;
      }
      return gcd;
    }

    void printTree() {
      for(int i : segmentTree) {
        cout << i << " ";
      }
      cout << endl;
    }
};

int main() {
  vector<int> arr = {6, 10, 8, 4, 16, 8, 4, 100};
  GCDSegmentTree tree(arr);
  tree.printTree();
  tree.updateTree(0, 1);
  tree.printTree();
  cout << tree.gcd(2, 7);
}
