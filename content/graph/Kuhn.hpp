#pragma once
#include "../template/Header.hpp"

/**
 * Author: Borworntat D.
 * Date: 2024-01-26
 * Description: Kuhn Algorithm to find maximum bipartite matching or find augmenting path in bipartite graph.
 * Time: $O(VE)$
 */

vi adj[1010], match(1010, -1);
vector<bool> visited(1010, false);
bool try_match(int u) {
  if(visited[u]) {
    return false;
  } 
  visited[u] = true;
  for(auto x: adj[u]) {
    if(match[x] == -1 || try_match(match[x])) {
      match[x] = u;
      return true;
    }
  }
  return false;
}

int max_matching() {
  for(int u=0; u<1010; ++u) {
    visited = vector<bool> (1010, false);
    try_match(u);
  }
  int cnt = 0;
  for(int u=0; u<1010; ++u) {
    cnt += (match[u] != -1);
  }
  return cnt;
}
