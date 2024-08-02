#pragma once
#include "../template/Header.hpp"

/**
 * Author: Borworntat D.
 * Date: 2024-08-02
 * Description: Optimize $O(N^2K)$ to $O(NK\log{N})$
 */

vector<vl> cst, dp;

ll cost(int l, int r) {
  return cst[l][r];
}

void divide(int l, int r, int opt_l, int opt_r, int c) {
  if(l > r) return ;
  int mid = (l + r) / 2;
  pair<ll, int> best = make_pair(INF, -1);
  for(int k=opt_l; k<=min(mid, opt_r); ++k) {
    best = min(best, make_pair(dp[c - 1][k] + cost(k + 1, mid), k));
  }
  dp[c][mid] = best.first;
  divide(l, mid - 1, opt_l, best.second, c);
  divide(mid + 1, r, best.second, opt_r, c);
}

// for(int c=1; c<=K; ++c) divide(1, N, 1, N, c);