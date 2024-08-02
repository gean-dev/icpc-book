#pragma once

/**
 * Author: Teetat T.
 * Date: 2024-01-15
 * Description: Fenwick / Binary Indexed Tree
 */

template<class T>
struct Fenwick{
    int n,logn;
    vector<T> t;
    Fenwick(){}
    Fenwick(int _n){init(vector<T>(_n,T{}));}
    template<class U>
    Fenwick(const vector<U> &a){init(a);}
    template<class U>
    void init(const vector<U> &a){
        n=(int)a.size();
        logn=31-__builtin_clz(n);
        t.assign(n+1,T{});
        for(int i=1;i<=n;i++){
            t[i]=t[i]+a[i-1];
            int j=i+(i&-i);
            if(j<=n)t[j]=t[j]+t[i];
        }
    }
    void update(int x,const T &v){
        for(int i=x+1;i<=n;i+=i&-i)t[i]=t[i]+v;
    }
    void update(int l,int r,const T &v){
        update(l,v),update(r+1,-v);
    }
    T query(int x){
        T res{};
        for(int i=x+1;i>0;i-=i&-i)res=res+t[i];
        return res;
    }
    T query(int l,int r){
        return query(r)-query(l-1);
    }
    int find(const T &k){
        int x=0;
        T cur{};
        for(int i=1<<logn;i>0;i>>=1)
            if(x+i<=n&&cur+t[x+i]<=k)x+=i,cur=cur+t[x];
        return x;
    }
};

