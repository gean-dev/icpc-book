#include "../../content/monoid/Add.hpp"

int main(){
  assert(AddMonoid<int>::op(1,2)==3);
  assert(AddMonoid<int>::op(3,2)==5);
  assert(AddMonoid<int>::op(100,10)==110);
  cout << "Test Passed!" << endl;
}