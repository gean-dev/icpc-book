#pragma once
#include "Dinic.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-07-1ุ6
 * Description: Binary Optimization.
 *  minimize $\kappa + \sum_i \theta_i(x_i) + \sum_{i<j} \phi_{ij}(x_i,x_j) + \sum_{i<j<k} \psi_{ijk}(x_i,x_j,x_k)$
 *  where $x_i \in \{0,1\}$ and $\phi_{ij},\psi_{ijk}$ are submodular functions.
 *  a set function $f$ is submodular if $f(S) + f(T) \geq f(S \cap T) + f(S \cup T)$ for all $S,T$.
 *  $\phi_{ij}(0,1) + \phi_{ij}(1,0) \geq \phi_{ij}(1,1) + \phi_{ij}(0,0)$.
 */

template<class T,bool minimize=true>
struct BinaryOptimization{
    static constexpr T INF=numeric_limits<T>::max()/2;
    int n,s,t,node_id;
    T base;
    map<pair<int,int>,T> edges;
    BinaryOptimization(int _n):n(_n),s(n),t(n+1),node_id(n+2),base(0){}
    void add_edge(int u,int v,T w){
        assert(w>=0);
        if(u==v||w==0)return;
        auto &e=edges[{u,v}];
        e=min(e+w,INF);
    }
    void add0(T w){
        base+=w;
    }
    void _add1(int i,T a,T b){
        if(a<=b){
            add0(a);
            add_edge(s,i,b-a);
        }else{
            add0(b);
            add_edge(i,t,a-b);
        }
    }
    void add1(int i,T x0,T x1){
        assert(0<=i&&i<n);
        if(!minimize)x0=-x0,x1=-x1;
        _add1(i,x0,x1);
    }
    void _add2(int i,int j,T a,T b,T c,T d){
        assert(b+c>=a+d);
        add0(a);
        _add1(i,0,c-a);
        _add1(j,0,d-c);
        add_edge(i,j,b+c-a-d);
    }
    void add2(int i,int j,T x00,T x01,T x10,T x11){
        assert(i!=j&&0<=i&&i<n&&0<=j&&j<n);
        if(!minimize)x00=-x00,x01=-x01,x10=-x10,x11=-x11;
        _add2(i,j,x00,x01,x10,x11);
    }
    void _add3(int i,int j,int k,T a,T b,T c,T d,T e,T f,T g,T h){
        T p=a+d+f+g-b-c-e-h;
        if(p>=0){
            add0(a);
            _add1(i,0,f-b);
            _add1(j,0,g-e);
            _add1(k,0,d-c);
            _add2(i,j,0,c+e-a-g,0,0);
            _add2(i,k,0,0,b+e-a-f,0);
            _add2(j,k,0,b+c-a-d,0,0);
            int u=node_id++;
            add0(-p);
            add_edge(i,u,p);
            add_edge(j,u,p);
            add_edge(k,u,p);
            add_edge(u,t,p);
        }else{
            add0(h);
            _add1(i,c-g,0);
            _add1(j,b-d,0);
            _add1(k,e-f,0);
            _add2(i,j,0,0,d+f-b-h,0);
            _add2(i,k,0,d+g-c-h,0,0);
            _add2(j,k,0,0,f+g-e-h,0);
            int u=node_id++;
            add0(p);
            add_edge(s,u,-p);
            add_edge(u,i,-p);
            add_edge(u,j,-p);
            add_edge(u,k,-p);
        }
    }
    void add3(int i,int j,int k,T x000,T x001,T x010,T x011,T x100,T x101,T x110,T x111){
        assert(i!=j&&j!=k&&k!=i&&0<=i&&i<n&&0<=j&&j<n&&0<=k&&k<n);
        if(!minimize){
            x000=-x000,x001=-x001,x010=-x010,x011=-x011;
            x100=-x100,x101=-x101,x110=-x110,x111=-x111;
        }
        _add3(i,j,k,x000,x001,x010,x011,x100,x101,x110,x111);
    }
    T solve(){
        Dinic<T> dinic(node_id,s,t);
        for(auto &[p,w]:edges){
            auto [u,v]=p;
            dinic.add_edge(u,v,w);
        }
        T ans=dinic.flow()+base;
        return minimize?ans:-ans;
    }
};