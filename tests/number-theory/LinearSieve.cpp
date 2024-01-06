#include <bits/stdc++.h>
#include "../../content/number-theory/LinearSieve.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  vi primes = linear_sieve(10000000);
  vector<pii> query = {
    {1024, 8161}, {178, 1061}, {10099, 105929}, {2090, 18233}, {2561, 22961}
  };
  for(auto &[q, a]: query) {
    assert(primes[q - 1] == a);
  }
  cout << "Tests passed!" << endl;
}