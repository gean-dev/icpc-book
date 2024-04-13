#pragma once
#include "../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2023-12-04
 * License: CC0
 * Description: Gaussian Elimination
 */

struct Gauss {
  int n, sz;
  vector<ll> basis;
  Gauss(int n = 0) {
    init(n);
  }
  void init(int _n) {
    n = _n, sz = 0;
    basis.assign(n, 0);
  }
  void insert(ll x) {
    for (int i = n - 1; i >= 0; i--)
      if (x >> i & 1) {
        if (!basis[i]) {
          basis[i] = x;
          sz++;
          return;
        }
        x ^= basis[i];
      }
  }
  ll getmax(ll k = 0) {
    ll tot = 1ll << sz, res = 0;
    for (int i = n - 1; i >= 0; i--)
      if (basis[i]) {
        tot >>= 1;
        if ((k >= tot && res >> i & 1) || (k < tot && res >> i & 1 ^ 1))
          res ^= basis[i];
        if (k >= tot)
          k -= tot;
      }
    return res;
  }
};

