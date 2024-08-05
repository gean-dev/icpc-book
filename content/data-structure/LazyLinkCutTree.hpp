#pragma once
#include "LazyReversibleSplayTree.hpp"
#include "LinkCutTreeBase.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-08-02
 * Description: Lazy Link Cut Tree.
 * Usage: using Lct = LazyLinkCutTree<Action>;
 *  using Ptr = Lct$\colon\colon$Ptr;
 *  using Node = Lct$\colon\colon$Node;
 *  vector<Ptr> ptr(n);
 *  for(int i=0;i<n;i++)ptr[i]=new Node(val[i]);
 *  auto link=[$\&$](int u,int v){
 *      Lct$\colon\colon$link(ptr[u],ptr[v]);
 *  };
 *  auto cut=[$\&$](int u,int v){
 *      Lct$\colon\colon$cut(ptr[u],ptr[v]);
 *  };
 *  auto update=[$\&$](int u,int v,const Action$\colon\colon$Tag $\&$val){
 *     Lct$\colon\colon$apply(ptr[u],ptr[v],val);
 *  };
 *  auto query=[$\&$](int u,int v){
 *     return Lct$\colon\colon$fold(ptr[u],ptr[v]);
 *  };
 */

template<class MonoidAction>
struct LazyLinkCutTree:LinkCutTreeBase<LazyReversibleSplayTree<MonoidAction>>{
    using base = LinkCutTreeBase<LazyReversibleSplayTree<MonoidAction>>;
    using Ptr = typename base::Ptr;
    using Tag = typename MonoidAction::Tag;

    void apply(Ptr u,Ptr v,const Tag &val){
        this->evert(u);
        this->expose(v);
        this->propagate(v,val);
    }
};

