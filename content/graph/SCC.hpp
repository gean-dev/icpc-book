#pragma once
#include "../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-06-28
 * Description: Strongly Connected Component.
 */

template<class G>
pair<int,vector<int>> strongly_connected_component(G &g){
    static_assert(G::is_directed);
    int n=g.n;
    vector<int> disc(n,-1),low(n),scc(n,-1);
    stack<int> st;
    vector<bool> in_st(n);
    int t=0,scc_cnt=0;
    function<void(int,int)> dfs=[&](int u,int p){
        disc[u]=low[u]=t++;
        st.emplace(u);
        in_st[u]=true;
        for(int v:g[u]){
            if(disc[v]==-1){
                dfs(v,u);
                low[u]=min(low[u],low[v]);
            }else if(in_st[v]){
                low[u]=min(low[u],disc[v]);
            }
        }
        if(disc[u]==low[u]){
            while(true){
                int v=st.top();
                st.pop();
                in_st[v]=false;
                scc[v]=scc_cnt;
                if(v==u)break;
            }
            scc_cnt++;
        }
    };
    for(int i=0;i<n;i++)if(disc[i]==-1)dfs(i,-1);
    return {scc_cnt,scc};
}