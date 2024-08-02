#include "../../content/template/Header.hpp"
#include "../../content/graph/HopcroftKarp.hpp"

using namespace std;

int main() {
  HopcroftKarp mbm;
  mbm.init(3, 3);
  mbm.addEdge(1, 1);
  assert(4 - mbm.maxMatching() * 2 == 2);

  HopcroftKarp mbm2;
  mbm2.init(3, 3);
  mbm.addEdge(1, 1);
  mbm.addEdge(1, 1);
  assert(5 - mbm.maxMatching() * 2 == 3);

  cout << "Test Passed!";
}
