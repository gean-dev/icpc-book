#pragma once
#include "../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-01-15
 * Description: Sparse Segment Tree
 */

template<class MonoidAction>
struct SparseSegmentTree{
    using InfoMonoid = typename MonoidAction::InfoMonoid;
    using TagMonoid = typename MonoidAction::TagMonoid;
    using Info = typename MonoidAction::Info;
    using Tag = typename MonoidAction::Tag;
    struct Node;
    using Ptr = Node*;
    struct Node{
        Info val;
        Tag lz;
        Ptr l,r;
        Node():val(InfoMonoid::unit()),lz(TagMonoid::unit()),l(nullptr),r(nullptr){}
        Node(Info v,Tag t):val(v),lz(t),l(nullptr),r(nullptr){}
    };
    ll lb,ub;
    Ptr rt;
    SparseSegmentTree(){}
    SparseSegmentTree(ll n){init(0,n-1);}
    SparseSegmentTree(ll lb,ll ub){init(lb,ub);}
    void init(ll _lb,ll _ub){
        lb=_lb,ub=_ub,rt=new Node();
    }
    Info val(Ptr t){
        return t?t->val:InfoMonoid::unit();
    }
    void pull(Ptr &t){
        t->val=InfoMonoid::op(val(t->l),val(t->r));
    }
    void apply(Ptr &t,const Tag &v){
        if(!t)t=new Node();
        t->val=MonoidAction::op(t->val,v);
        t->lz=TagMonoid::op(t->lz,v);
    }
    void push(Ptr &t){
        apply(t->l,t->lz);
        apply(t->r,t->lz);
        t->lz=TagMonoid::unit();
    }
    void modify(ll l,ll r,Ptr &t,ll x,const Info &v){
        if(x<l||r<x)return;
        if(l==r)return void(t->val=v);
        ll m=l+(r-l)/2;
        push(t);
        modify(l,m,t->l,x,v);
        modify(m+1,r,t->r,x,v);
        pull(t);
    }
    void modify(ll x,const Info &v){
        modify(lb,ub,rt,x,v);
    }
    void update(ll l,ll r,Ptr &t,ll x,ll y,const Tag &v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(t,v);
        ll m=l+(r-l)/2;
        push(t);
        update(l,m,t->l,x,y,v);
        update(m+1,r,t->r,x,y,v);
        pull(t);
    }
    void update(ll x,ll y,const Tag &v){
        update(lb,ub,rt,x,y,v);
    }
    Info query(ll l,ll r,Ptr &t,ll x,ll y){
        if(y<l||r<x)return InfoMonoid::unit();
        if(x<=l&&r<=y)return t->val;
        ll m=l+(r-l)/2;
        push(t);
        return InfoMonoid::op(query(l,m,t->l,x,y),query(m+1,r,t->r,x,y));
    }
    Info query(ll x,ll y){
        return query(lb,ub,rt,x,y);
    }
    template<class F>
    ll findfirst(ll l,ll r,Ptr t,ll x,ll y,const F &f){
        if(y<l||r<x||!f(t->val))return -1;
        if(l==r)return l;
        ll m=l+(r-l)/2;
        push(t);
        ll res=findfirst(l,m,t->l,x,y,f);
        if(res==-1)res=findfirst(m+1,r,t->r,x,y,f);
        return res;
    }
    template<class F>
    ll findfirst(ll x,ll y,const F &f){
        return findfirst(lb,ub,rt,x,y,f);
    }
    template<class F>
    ll findlast(ll l,ll r,Ptr t,ll x,ll y,const F &f){
        if(y<l||r<x||!t||!f(t->val))return -1;
        if(l==r)return l;
        ll m=l+(r-l)/2;
        push(t);
        ll res=findlast(m+1,r,t->r,x,y,f);
        if(res==-1)res=findlast(l,m,t->l,x,y,f);
        return res;
    }
    template<class F>
    ll findlast(ll x,ll y,const F &f){
        return findlast(lb,ub,rt,x,y,f);
    }
};

