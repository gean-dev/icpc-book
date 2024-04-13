#pragma once
#include "../template/Header.hpp"

/**
 * Author: Borworntat D.
 * Date: 2024-01-26
 * Description: Kuhn Algorithm to find maximum bipartite matching or find augmenting path in bipartite graph.
 * Time: $O(VE)$
 */

vi adj[1010], match(1010, -1);
bitset<1010> visited;
bool kuhn(int u) {
  if(visited[u]) {
    return false;
  } 
  visited[u] = true;
  for(auto x: adj[u]) {
    if(match[x] == -1 || kuhn(match[x])) {
      match[x] = u;
      return true;
    }
  }
  return false;
}

