#pragma once
#include "../template/Header.hpp"

/**
 * Author: Borworntat D.
 * Date: 2024-01-06
 * License: CC0
 * Source: https://cp-algorithms.com/algebra/prime-sieve-linear.html
 * Description: Prime Number Generator in Linear Time
 * Time: $O(N)$
 */

vi linear_sieve(int n) {
  vi prime, composite(n + 1);
  for(int i=2; i<=n; ++i) {
    if(!composite[i]) {
      prime.emplace_back(i);
    }
    for(int j=0; j<(int) prime.size() && i*prime[j]<=n; ++j) {
      composite[i * prime[j]] = true;
      if(i % prime[j] == 0) {
        break;
      }
    }
  }
  return prime;
}

