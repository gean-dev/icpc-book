#include <bits/stdc++.h>
#include "../../content/data-structure/SparseTable.hpp"

int main() {
  vector<int> a = {1, 3, 2, 4, 2, 9, 2};
  SparseTable<int> s1(a);
  assert(s1.query(0, 4) == 1);
  assert(s1.query(5, 7) == 2);
  assert(s1.query(3, 4) == 4);
  cout << "Test Passed!";
}