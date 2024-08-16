#pragma once
#include "Dinic.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-07-16
 * Description: k-ary Optimization.
 * minimize $\kappa + \sum_i \theta_i(x_i) + \sum_{i<j} \phi_{ij}(x_i,x_j)$
 * where $x_i \in \{0,1,\ldots,k-1\}$ and $\phi_{i,j}$ is monge.
 * A function $f$ is monge if $f(a,c)+f(b,d) \leq f(a,d)+f(b,c)$ for all $a < b$ and $c < d$.
 * $\phi_{ij}(x-1,y)+\phi_{ij}(x,y+1) \leq \phi_{ij}(x-1,y+1)+\phi_{ij}(x,y)$.
 * $\phi_{ij}(x,y)+\phi_{ij}(x-1,y+1)-\phi_{ij}(x-1,y)-\phi_{ij}(x,y+1) \geq 0$.
 */

template<class T,bool minimize=true>
struct K_aryOptimization{
    static constexpr T INF=numeric_limits<T>::max()/2;
    int n,s,t,node_id;
    T base;
    vector<int> ks;
    vector<vector<int>> id;
    map<pair<int,int>,T> edges;
    K_aryOptimization(int n,int k){init(vector<int>(n,k));}
    K_aryOptimization(const vector<int> &_ks){init(_ks);}
    void init(const vector<int> &_ks){
        ks=_ks;
        n=ks.size();
        s=0,t=1,node_id=2;
        base=0;
        id.clear();
        edges.clear();
        for(auto &k:ks){
            assert(k>=1);
            vector<int> a(k+1);
            a[0]=s,a[k]=t;
            for(int i=1;i<k;i++)a[i]=node_id++;
            id.emplace_back(a);
            for(int i=2;i<k;i++)add_edge(a[i],a[i-1],INF);
        }
    }
    void add_edge(int u,int v,T w){
        assert(w>=0);
        if(u==v||w==0)return;
        auto &e=edges[{u,v}];
        e=min(e+w,INF);
    }
    void add0(T w){
        base+=w;
    }
    void _add1(int i,vector<T> cost){
        add0(cost[0]);
        for(int j=1;j<ks[i];j++){
            T x=cost[j]-cost[j-1];
            if(x>0)add_edge(id[i][j],t,x);
            if(x<0)add0(x),add_edge(s,id[i][j],-x);
        }
    }
    void add1(int i,vector<T> cost){
        assert(0<=i&&i<n&&(int)cost.size()==ks[i]);
        if(!minimize)for(auto &x:cost)x=-x;
        _add1(i,cost);
    }
    void _add2(int i,int j,vector<vector<T>> cost){
        int h=ks[i],w=ks[j];
        _add1(j,cost[0]);
        for(int x=h-1;x>=0;x--)for(int y=0;y<w;y++)cost[x][y]-=cost[0][y];
        vector<T> a(h);
        for(int x=0;x<h;x++)a[x]=cost[x][w-1];
        _add1(i,a);
        for(int x=0;x<h;x++)for(int y=0;y<w;y++)cost[x][y]-=a[x];
        for(int x=1;x<h;x++){
            for(int y=0;y<w-1;y++){
                T w=cost[x][y]+cost[x-1][y+1]-cost[x-1][y]-cost[x][y+1];
                assert(w>=0); // monge
                add_edge(id[i][x],id[j][y+1],w);
            }
        }
    }
    void add2(int i,int j,vector<vector<T>> cost){
        assert(0<=i&&i<n&&0<=j&&j<n&&i!=j);
        assert((int)cost.size()==ks[i]);
        for(auto &v:cost)assert((int)v.size()==ks[j]);
        if(!minimize)for(auto &v:cost)for(auto &x:v)x=-x;
        _add2(i,j,cost);
    }
    pair<T,vector<int>> solve(){
        Dinic<T> dinic(node_id,s,t);
        for(auto &[p,w]:edges){
            auto [u,v]=p;
            dinic.add_edge(u,v,w);
        }
        auto [val,cut]=dinic.cut();
        val+=base;
        if(!minimize)val=-val;
        vector<int> ans(n);
        for(int i=0;i<n;i++){
            ans[i]=ks[i]-1;
            for(int j=1;j<ks[i];j++)ans[i]-=cut[id[i][j]];
        }
        return {val,ans};
    }
};