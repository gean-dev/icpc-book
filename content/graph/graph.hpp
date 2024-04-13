#pragma once
#include "../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-05
 * Description: Graph base template.
 */

template<class T>
struct Edge{
    int from,to;
    T cost;
    Edge(int _to,T _cost):from(-1),to(_to),cost(_cost){}
    Edge(int _from,int _to,T _cost):from(_from),to(_to),cost(_cost){}
    Edge &operator=(const int &x){
        to=x;
        return *this;
    }
    operator int()const{
        return to;
    }
};

template<class T=int,bool directed=false>
struct Graph{
    static constexpr bool is_directed=directed;
    using cost_t = T;
    using edge_t = Edge<T>;
    int n,m;
    vector<edge_t> edges;
    vector<vector<edge_t>> adj;
    vector<int> deg,indeg,outdeg;
    Graph(int _n=0){
        init(_n);
    }
    void init(int _n){
        n=_n,m=0;
        edges.clear();
        adj.assign(n,vector<edge_t>{});
    }
    void add(int from,int to,T cost=1){
        assert(0<=from&&from<n&&0<=to&&to<n);
        edges.emplace_back(edge_t(from,to,cost));
        adj[from].emplace_back(edge_t(from,to,cost));
        if(!directed)adj[to].emplace_back(edge_t(to,from,cost));
        m++;
    }
    void read(int _m,bool weighted=false,int offset=1){
        for(int i=0;i<_m;i++){
            int u,v;
            cin >> u >> v;
            u-=offset,v-=offset;
            if(weighted){
                T w;
                cin >> w;
                add(u,v,w);
            }else{
                add(u,v);
            }
        }
    }
    void calc_deg(){
        if(!deg.empty())return;
        deg.assign(n,0);
        for(auto &&e:edges)deg[e.from]++,deg[e.to]++;
    }
    void calc_deginout(){
        if(!indeg.empty()||!outdeg.empty())return;
        indeg.assign(n,0),outdeg.assign(n,0);
        for(auto &&e:edges)outdeg[e.from]++,indeg[e.to]++;
    }
    vector<int> deg_array(){
        calc_deg();
        return deg;
    }
    vector<int> indeg_array(){
        calc_deginout();
        return indeg;
    }
    vector<int> outdeg_array(){
        calc_deginout();
        return outdeg;
    }
    int get_deg(int u){
        calc_deg();
        return deg[u];
    }
    int get_indeg(int u){
        calc_deginout();
        return indeg[u];
    }
    int get_outdeg(int u){
        calc_deginout();
        return outdeg[u];
    }
};

