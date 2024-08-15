#pragma once
#include "../template/Header.hpp"

/**
 * Author: Borworntat D.
 * Date: 2024-08-15
 * License: CC0
 * Description: Centroid
 */

vector<vi> adj;
vi sz;
vector<bool> used;

int find_size(int u, int p) {
  sz[u] = 1;
  for(auto v: adj[u]) {
    if(v == p || used[v]) continue;
    sz[u] += find_size(v, u);
  }
  return sz[u];
}

int find_cen(int u, int p, int t) {
  for(auto v: adj[u]) {
    if(v == p || used[v]) continue;
    if(sz[v] * 2 > t) find_cen(v, u, t);
  }
  return u;
}

void decom(int u) {
  u = find_cen(u, 0, find_size(u, 0));
  used[u] = true;
  for(auto v: adj[u]) {
    // dfs do something
  }
  for(auto v: adj[u]) {
    if(used[v]) continue;
    decom(v);
  }
}