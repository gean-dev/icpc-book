/**
 * Author: Borworntat D.
 * Date: 2024-02-26
 * Description: Sparse Table
 * Usage:
 *  SparseTable<T> s(vector<T>)
 *  s.query(l, r + 1)
 */

#pragma once
#include "../template/Header.hpp"

template<class T>
struct SparseTable {
  vector<vector<T>> t;
  SparseTable(vector<T> v): t(1, v) {
    for(int p=1, k=1; p*2<=sz(v); p*=2, ++k) {
      t.emplace_back(sz(v) - p * 2 + 1);
      for(int j=0; j<sz(t[k]); ++j) {
        t[k][j] = min(t[k - 1][j], t[k - 1][j + p]);
      }
    }
  }
  T query(int l, int r) {
    int lg = 31 - __builtin_clz(r - l);
    return min(t[lg][l], t[lg][r - (1 << lg)]);
  }
};