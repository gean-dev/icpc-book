#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> p2;

template<class T>
struct segtree{
    int n;
    vector<T> t;
    segtree(){}
    segtree(int _n){
        n=_n;
        t.assign(4*n,0);
    }
    void build(int l,int r,int i,vector<T> &a){
        if(l==r)return void(t[i]=a[l]);
        int m=(l+r)/2;
        build(l,m,i*2,a);
        build(m+1,r,i*2+1,a);
    }
    void build(vector<T> a){
        build(1,n,1,a);
    }
    void update(int l,int r,int i,int &x,int &v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    update(int x,int v){
        update(1,n,1,x,v);
    }
    void query(int l,int r,int i,int &x,int &y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    void query(int x,int y){
        return query(1,n,1,x,y);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    
}