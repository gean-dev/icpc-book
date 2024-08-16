#pragma once
#include "../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-08-17
 * License: CC0
 * Description: Static Top Tree
 * Status: Tested
 */

enum Type{Compress,Rake,AddEdge,AddVertex,Vertex};

struct StaticTopTree{
    int n,node_id;
    int root,stt_root;
    vector<vector<int>> &adj;
    vector<int> hv;
    vector<int> lch,rch,par;
    vector<Type> type;
    StaticTopTree(vector<vector<int>> &_adj,int _root):adj(_adj){
        n=adj.size();
        root=_root;
        node_id=n;
        hv.assign(n,-1);
        lch.assign(4*n,-1);
        rch.assign(4*n,-1);
        par.assign(4*n,-1);
        type.assign(4*n,Type::Vertex);
        dfs(root);
        stt_root=compress(root).first;
    }
    int dfs(int u){
        int mx=0,sz=1;
        for(auto v:adj[u]){
            int x=dfs(v);
            sz+=x;
            if(x>mx){
                hv[u]=v;
                mx=x;
            }
        }
        return sz;
    }
    int add(int i,int l,int r,Type t){
        if(i==-1)i=node_id++;
        lch[i]=l,rch[i]=r,par[i]=-1,type[i]=t;
        if(l!=-1)par[l]=i;
        if(r!=-1)par[r]=i;
        return i;
    }
    pair<int,int> merge(vector<pair<int,int>> a,Type t){
        if(a.size()==1)return a[0];
        int tot=0;
        vector<pair<int,int>> l,r;
        for(auto [i,s]:a)tot+=s;
        for(auto [i,s]:a){
            if(tot>s)l.emplace_back(i,s);
            else r.emplace_back(i,s);
            tot-=s*2;
        }
        auto [i,si]=merge(l,t);
        auto [j,sj]=merge(r,t);
        return {add(-1,i,j,t),si+sj};
    }
    pair<int,int> compress(int i){
        vector<pair<int,int>> a{add_vertex(i)};
        while(hv[i]!=-1)a.emplace_back(add_vertex(i=hv[i]));
        return merge(a,Type::Compress);
    }
    pair<int,int> rake(int i){
        vector<pair<int,int>> a;
        for(auto j:adj[i])if(j!=hv[i])a.emplace_back(add_edge(j));
        return a.empty()?make_pair(-1,0):merge(a,Type::Rake);
    }
    pair<int,int> add_edge(int i){
        auto [j,s]=compress(i);
        return {add(-1,j,-1,Type::AddEdge),s};
    }
    pair<int,int> add_vertex(int i){
        auto [j,s]=rake(i);
        return {add(i,j,-1,j==-1?Type::Vertex:Type::AddVertex),s+1};
    }
};

const int N=2e5+5;

int n,q;
ll a[N];
vector<vector<int>> adj;

using Path = pair<ll,ll>;
using Point = ll;

Path compress(Path p,Path ch){
    auto [a,b]=ch;
    auto [c,d]=p;
    return {a*c%MOD,(b*c+d)%MOD};
}

Point rake(Point l,Point r){
    return l*r%MOD;
}

Path add_vertex(Point x,int i){
    return {x,a[i]};
}

Point add_edge(Path x){
    return x.second;
}

Path vertex(int i){
    return {1LL,a[i]};
}

Path path[4*N];
Point point[4*N];

void example(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    adj.resize(n);
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        adj[p-1].emplace_back(i);
    }
    for(int i=0;i<n;i++)cin >> a[i];
    StaticTopTree stt(adj,0);
    auto update=[&](int i){
        if(stt.type[i]==Type::Compress){
            path[i]=compress(path[stt.lch[i]],path[stt.rch[i]]);
        }else if(stt.type[i]==Type::Rake){
            point[i]=rake(point[stt.lch[i]],point[stt.rch[i]]);
        }else if(stt.type[i]==Type::AddVertex){
            path[i]=add_vertex(point[stt.lch[i]],i);
        }else if(stt.type[i]==Type::AddEdge){
            point[i]=add_edge(path[stt.lch[i]]);
        }else{
            path[i]=vertex(i);
        }
    };
    function<void(int)> dfs=[&](int u){
        if(u==-1)return;
        dfs(stt.lch[u]);
        dfs(stt.rch[u]);
        update(u);
    };
    dfs(stt.stt_root);
    while(q--){
        int v,x;
        cin >> v >> x;
        v--;
        a[v]=x;
        for(;v!=-1;v=stt.par[v])update(v);
        cout << path[stt.stt_root].second << "\n";
    }
}