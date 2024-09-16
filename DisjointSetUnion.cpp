#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// CodeForces problem: Roads not only in Berland

class DisjointSetUnion {
  private:
    vector<int> parents;
    vector<int> sizes;

  public:
    DisjointSetUnion(int size) : parents(size + 1), sizes(size + 1, 1){
      for(int i = 0; i < size + 1; ++i) {
        parents[i] = i;
      }
    }

    int find(int x) {
      if(parents[x] != x) {
        return find(parents[x]);
      }
      return x;
    }

    void unite(int x, int y) {
      int parentX = find(x);
      int parentY = find(y);

      if(parentX == parentY) return;
      int sizeX = sizes[parentX];
      int sizeY = sizes[parentY];

      if(sizeX < sizeY) {
        parents[parentX] = parentY;
        sizeY += sizeX;
      }
      else {
        parents[parentY] = parentX;
        sizeX += sizeY;
      }
    }

    bool isConnected(int x, int y) {
      return find(x) == find(y);
    }

    vector<int> getParents() {
      return parents;
    }
};

int main() {
  int size;
  cin >> size;
  DisjointSetUnion roads(size);
  vector<pair<int, int>> redundant;
  vector<int> unconnected;

  for(int i = 0; i < size - 1; ++i) {
    int x, y;
    cin >> x >> y;
    if(roads.isConnected(x, y)) {
      pair<int, int> conn;
      conn.first = x;
      conn.second = y;
      redundant.push_back(conn);
    }
    roads.unite(x, y);
  }
  vector<int> parents = roads.getParents();
  /*for(int i : parents) {
    cout << i << " ";
  }*/
  cout << endl;
  
  unordered_set<int> uniqueParents;
  for(int i = 1; i < parents.size(); ++i) {
    if(!uniqueParents.count(parents[i])) {
      uniqueParents.insert(parents[i]);
      unconnected.push_back(parents[i]);
    }
  }
  
  cout << unconnected.size() - 1 << endl;
  if(unconnected.size() > 1) {
    int redundantIndex = 0;
    for(int i = 1; i < unconnected.size(); ++i) {
      cout << redundant[redundantIndex].first << " " << redundant[redundantIndex].second << " " << unconnected[0] << " " << unconnected[i] << endl;
    }
  }
}
