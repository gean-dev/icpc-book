#pragma once
#include "../template/Header.hpp"

/**
 * Author: Borworntat D.
 * Date: 2024-08-15
 * License: CC0
 * Description: HLD
 */

vector<vi> adj;
vector<int> sz, lvl, hv, hd, p, disc;
int t;

void dfs(int u, int parent) {
  sz[u] = 1;
  lvl[u] = lvl[parent] + 1;
  p[u] = parent;
  int c_hv=0, c_max=0;
  for(auto v: adj[u]) {
    if(v == parent) continue;
    dfs(v, u);
    sz[u] += sz[v];
    if(c_max < sz[v]) {
      c_hv = v;
      c_max = sz[v];
    }
  }
  hv[u] = c_hv;
}

void hld(int u, int parent) {
  if(hd[u] == 0) {
    hd[u] = u;
  }
  disc[u] = ++t;
  if(hv[u] != 0) {
    hd[hv[u]] = hd[u];
    hld(hv[u], u);
  }
  for(auto v: adj[u]) {
    if(v == parent || v == hv[u]) {
      continue;
    }
    hld(v, u);
  }
}

int lca(int u, int v) {
  while(hd[u] != hd[v]) {
    if(lvl[hd[u]] > lvl[hd[v]]) swap(u, v);
    v=p[hd[v]];
  }
  return lvl[u] < lvl[v] ? u: v;
}