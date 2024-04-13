/**
 * Author: Teetat T.
 * Date: 2024-04-13
 * Description: template for revesible BBST.
 */

#pragma once
#include "../template/Header.hpp"

template<class Tree,class Node,class T,T (*combine)(T,T),T (*flip)(T)>
struct ReversibleBBST:Tree{
    using Tree::merge;
    using Tree::split;
    using Ptr = Node*;

    ReversibleBBST()=default;

    T sum(Ptr t){
        return t?t->sum:T();
    }
    void pull(Ptr t){
        if(!t)return;
        t->size=1;
        t->sum=t->val;
        if(t->l)t->size+=t->l->size,t->sum=combine(t->l->sum,t->sum);
        if(t->r)t->size+=t->r->size,t->sum=combine(t->sum,t->r->sum);
    }
    void push(Ptr t){
        if(!t)return;
        if(t->rev){
            toggle(t->l);
            toggle(t->r);
            t->rev=false;
        }
    }
    void toggle(Ptr t){
        if(!t)return;
        swap(t->l,t->r);
        t->sum=flip(t->sum);
        t->rev^=true;
    }
    T query(Ptr &t,int l,int r){
        if(l>r)return T();
        auto x=split(t,l);
        auto y=split(x.second,r-l+1);
        T res=sum(y.first);
        t=merge(x.first,merge(y.first,y.second));
        return res;
    }
    void reverse(Ptr &t,int l,int r){
        if(l>r)return;
        auto x=split(t,l);
        auto y=split(x.second,r-l+1);
        toggle(y.first);
        t=merge(x.first,merge(y.first,y.second));
    }
};