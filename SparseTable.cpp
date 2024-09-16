#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

// Find the minimum value of each subarray in an array

vector<vector<int>> sparseTable(vector<int>);

int main() {
  vector<int> arr = {10, 20, 7, 6, 7, 3, 5, 1, 14, 89};
  for(vector<int> i : sparseTable(arr)) {
    for(int j : i) {
      cout << j << " ";
    }
    cout << endl;
  }
}

vector<vector<int>> sparseTable(vector<int> arr) {
  int numRows = ceil((log(arr.size()) / log(2)));
  int numCol = arr.size();
  vector<vector<int>> st(numRows, vector<int>(numCol));
  for(int j = 0; j < numCol; ++j) {
    st[0][j] = arr[j];
  }

  for(int i = 1; i < numRows; ++i) {
    for(int j = 0; j + (1 << i) <= numCol; ++j) {
      st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
  return st;
}
