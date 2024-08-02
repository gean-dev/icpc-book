#pragma once

/**
 * Author: Teetat T.
 * Date: 2024-06-11
 * Description: Binary Trie
 */

template<int BIT,class T = uint32_t,class S = int>
struct BinaryTrie{
    struct Node{
        array<int,2> ch;
        S cnt;
        Node():ch{-1,-1},cnt(0){}
    };
    vector<Node> t;
    BinaryTrie():t{Node()}{}
    int new_node(){
        t.emplace_back(Node());
        return t.size()-1;
    }
    S size(){
        return t[0].cnt;
    }
    bool empty(){
        return size()==0;
    }
    S get_cnt(int i){
        return i!=-1?t[i].cnt:S(0);
    }
    void insert(T x,S k=1){
        int u=0;
        t[u].cnt+=k;
        for(int i=BIT-1;i>=0;i--){
            int v=x>>i&1;
            if(t[u].ch[v]==-1)t[u].ch[v]=new_node();
            u=t[u].ch[v];
            t[u].cnt+=k;
        }
    }
    void erase(T x,S k=1){
        int u=0;
        assert(t[u].cnt>=k);
        t[u].cnt-=k;
        for(int i=BIT-1;i>=0;i--){
            int v=x>>i&1;
            u=t[u].ch[v];
            assert(u!=-1&&t[u].cnt>=k);
            t[u].cnt-=k;
        }
    }
    T kth(S k,T x=0){
        assert(k<size());
        int u=0;
        T res=0;
        for(int i=BIT-1;i>=0;i--){
            int v=x>>i&1;
            if(k<get_cnt(t[u].ch[v])){
                u=t[u].ch[v];
            }else{
                res|=T(1)<<i;
                k-=get_cnt(t[u].ch[v]);
                u=t[u].ch[v^1];
            }
        }
        return res;
    }
    T min(T x){
        return kth(0,x);
    }
    T max(T x){
        return kth(size()-1,x);
    }
};

