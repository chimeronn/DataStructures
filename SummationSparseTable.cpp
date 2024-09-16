#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

// Find the total sum of every subarray in an array

vector<vector<int>> sumSparseTable(vector<int>);

int main() {
  vector<int> arr = {10, 20, 7, 6, 7, 3, 5, 1, 14, 89};
  for(vector<int> i : sumSparseTable(arr)) {
    for(int j : i) {
      cout << j << " ";
    }
    cout << endl;
  }
}

vector<vector<int>> sumSparseTable(vector<int> arr) {
  int numRows = ceil(log(arr.size()) / log(2));
  int numCol = arr.size();
  vector<vector<int>> sst(numRows, vector<int>(numCol));

  for(int i = 0; i < numCol; ++i) {
    sst[0][i] = arr[i];
  }

  for(int i = 1; i < numRows; ++i) {
    for(int j = 0; j + (1 << i) <= numCol; ++j) {
      sst[i][j] = sst[i - 1][j] + sst[i - 1][j + (1 << (i - 1))];
    }
  }
  return sst;
}
