#include <iostream>
#include <vector>
using namespace std;

void updateTree(vector<int>&, int, int);

int getSum(vector<int>, int);

vector<int> constructTree(vector<int> arr) {
  vector<int> fenwickTree(arr.size() + 1);
  for(int i = 1; i < fenwickTree.size(); ++i) {
    updateTree(fenwickTree, i, arr[i - 1]);
  }
  return fenwickTree;
}

int main() {
  vector<int> arr = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<int> fenwickTree = constructTree(arr);
  for(int i : fenwickTree) {
    cout << i << " ";
  }
  cout << endl;
  cout << getSum(fenwickTree, 12) << endl;
  cout << getSum(fenwickTree, 12) - getSum(fenwickTree, 3) << endl;
} 

void updateTree(vector<int>& fenwickTree, int index, int val) {
  int size = fenwickTree.size();
  while(index <= size) {
    fenwickTree[index] += val;
    index += (index & -index);
  }
}

int getSum(vector<int> fenwickTree, int endIndex) {
  int index = endIndex;
  int sum = 0;
  while(index > 0) {
    sum += fenwickTree[index];
    index -= (index & -index);
  }
  return sum;
}
