#pragma once

/**
 * Author: Teetat T.
 * Date: 2024-06-28
 * Description: Low Link.
 */

template<class G>
struct LowLink{
    G &g;
    int n;
    vector<int> disc,low,par,ord;
    vector<pair<int,int>> bridge;
    vector<int> articulation;
    int t=0;
    LowLink(G &_g):g(_g),n(g.n),disc(n,-1),low(n),par(n,-1){
        for(int i=0;i<n;i++)if(disc[i]==-1)dfs(i);
    }
    void dfs(int u){
        disc[u]=low[u]=t++;
        ord.emplace_back(u);
        int child=0;
        bool found_par=false;
        for(int v:g[u]){
            if(disc[v]==-1){
                par[v]=u;
                dfs(v);
                low[u]=min(low[u],low[v]);
                if(low[v]>disc[u])bridge.emplace_back(u,v);
                if(par[u]!=-1&&low[v]>=disc[u])articulation.emplace_back(u);
                child++;
            }else if(v!=par[u]||found_par){
                low[u]=min(low[u],disc[v]);
            }else{
                found_par=true;
            }
        }
        if(par[u]==-1&&child>1)articulation.emplace_back(u);
    }
};