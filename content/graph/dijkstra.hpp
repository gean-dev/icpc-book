/**
 * Author: Teetat T.
 * Date: 2024-04-05
 * Description: Dijkstra algorithm for finding shortest path from single source in non-negative weighted graph.
 * Time: $O(E + V log V)$
 */
#pragma once
#include "graph.hpp"

template<class T=int,bool directed=false>
vector<T> dijkstra(const Graph<T,directed> &g,int source=0){
    using P = pair<T,int>;
    int n=g.n;
    vector<T> dist(n,T(-1));
    priority_queue<P,vector<P>,greater<P>> pq;
    dist[source]=0;
    pq.emplace(0,source);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(dist[u]<d)continue;
        for(auto &e:g.adj[u]){
            int v=e.to;
            T ndist=d+e.cost;
            if(dist[v]==T(-1)||ndist<dist[v]){
                dist[v]=ndist;
                pq.emplace(ndist,v);
            }
        }
    }
    return dist;
}