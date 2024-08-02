#include "../../content/template/Header.hpp"
#include "../../content/data-structure/SparseTable.hpp"
#include "../../content/monoid/Min.hpp"

int main() {
  vector<int> a = {1, 3, 2, 4, 2, 9, 2};
  SparseTable<MinMonoid<int>> s1(a);
  assert(s1.query(0, 3) == 1);
  assert(s1.query(5, 6) == 2);
  assert(s1.query(3, 3) == 4);
  cout << "Test Passed!";
}