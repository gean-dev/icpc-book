#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

vector<pair<int, int>> a = {{1, 2}, {4, 3}};
vector<int> b = {3, 7}; 

int main(int argc, char* argv[]) {
  for(int i=0; i<a.size(); ++i) {
    assert(a[i].first + a[i].second == b[i]);
  }
  cout << "PASSED";
}