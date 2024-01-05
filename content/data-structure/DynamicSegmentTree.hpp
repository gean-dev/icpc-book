#pragma once
#include "../template/Header.hpp"

/*
    Dynamic Segment Tree
    Verification:
        - https://cses.fi/problemset/task/2166
        - https://cses.fi/problemset/task/1735
*/

template<class Node,class Tag>
struct DynamicSegTree{
    struct node;
    using pnode = node*;
    struct node{
        Node val;
        Tag lz;
        pnode l,r;
        node():val(Node()),lz(Tag()),l(nullptr),r(nullptr){}
        node(Node v,Tag t):val(v),lz(t),l(nullptr),r(nullptr){}
    };
    ll n;
    pnode rt;
    DynamicSegTree(){}
    DynamicSegTree(ll n){init(n);}
    void init(ll _n){
        n=_n,rt=new node();
    }
    Node val(pnode t){
        return t?t->val:Node();
    }
    void pull(pnode &t){
        t->val=val(t->l)+val(t->r);
    }
    void apply(ll l,ll r,pnode &t,const Tag &v){
        if(!t)t=new node();
        t->val.apply(l,r,v);
        t->lz.apply(l,r,v);
    }
    void push(ll l,ll r,pnode &t){
        ll m=(l+r)/2;
        apply(l,m,t->l,t->lz);
        apply(m+1,r,t->r,t->lz);
        t->lz=Tag();
    }
    void modify(ll l,ll r,pnode &t,ll x,const Node &v){
        if(x<l||r<x)return;
        if(l==r)return void(t->val=v);
        ll m=(l+r)/2;
        push(l,r,t);
        modify(l,m,t->l,x,v);
        modify(m+1,r,t->r,x,v);
        pull(t);
    }
    void modify(ll x,const Node &v){
        modify(0,n-1,rt,x,v);
    }
    void update(ll l,ll r,pnode &t,ll x,ll y,const Tag &v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(l,r,t,v);
        ll m=(l+r)/2;
        push(l,r,t);
        update(l,m,t->l,x,y,v);
        update(m+1,r,t->r,x,y,v);
        pull(t);
    }
    void update(ll x,ll y,const Tag &v){
        update(0,n-1,rt,x,y,v);
    }
    Node query(ll l,ll r,pnode &t,ll x,ll y){
        if(y<l||r<x)return Node();
        if(x<=l&&r<=y)return t->val;
        ll m=(l+r)/2;
        push(l,r,t);
        return query(l,m,t->l,x,y)+query(m+1,r,t->r,x,y);
    }
    Node query(ll x,ll y){
        return query(0,n-1,rt,x,y);
    }
    template<class F>
    ll findfirst(ll l,ll r,pnode t,ll x,ll y,const F &f){
        if(y<l||r<x||!f(t->val))return -1;
        if(l==r)return l;
        ll m=(l+r)/2;
        push(l,r,t);
        ll res=findfirst(l,m,t->l,x,y,f);
        if(res==-1)res=findfirst(m+1,r,t->r,x,y,f);
        return res;
    }
    template<class F>
    ll findfirst(ll x,ll y,const F &f){
        return findfirst(0,n-1,rt,x,y,f);
    }
    template<class F>
    ll findlast(ll l,ll r,pnode t,ll x,ll y,const F &f){
        if(y<l||r<x||!t||!f(t->val))return -1;
        if(l==r)return l;
        ll m=(l+r)/2;
        push(l,r,t);
        ll res=findlast(m+1,r,t->r,x,y,f);
        if(res==-1)res=findlast(l,m,t->l,x,y,f);
        return res;
    }
    template<class F>
    ll findlast(ll x,ll y,const F &f){
        return findlast(0,n-1,rt,x,y,f);
    }
};
struct AddTag{
    ll val;
    AddTag():val(0){}
    AddTag(ll v):val(v){}
    void apply(ll l,ll r,const AddTag &v){
        val+=v.val;
    }
};
struct MaxNode{
    ll val;
    MaxNode():val(-LINF){}
    MaxNode(ll x):val(x){}
    void apply(ll l,ll r,const AddTag &v){
        val+=v.val;
    }
    friend MaxNode operator+(const MaxNode &lhs,const MaxNode &rhs){
        return MaxNode(max(lhs.val,rhs.val));
    }
};
struct MinNode{
    ll val;
    MinNode():val(LINF){}
    MinNode(ll v):val(v){}
    void apply(ll l,ll r,const AddTag &v){
        val+=v.val;
    }
    friend MinNode operator+(const MinNode &lhs,const MinNode &rhs){
        return MinNode(min(lhs.val,rhs.val));
    }
};
struct SumNode{
    ll val;
    SumNode():val(0){}
    SumNode(ll v):val(v){}
    void apply(ll l,ll r,const AddTag &v){
        val+=v.val*(r-l+1);
    }
    friend SumNode operator+(const SumNode &lhs,const SumNode &rhs){
        return SumNode(lhs.val+rhs.val);
    }
};

