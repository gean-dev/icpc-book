/**
 * Author: Teetat T.
 * Date: 2024-04-13
 * Description: Splay Tree. splay(u) will make node u be the root of the tree in amortized O(log n) time.
 */

#pragma once
#include "../template/Header.hpp"
#include "SplayTreeBase.hpp"
#include "ReversibleBBST.hpp"

template<class T>
struct ReversibleSplayTreeNode{
    using Ptr = ReversibleSplayTreeNode*;
    Ptr l,r,p;
    T val,sum;
    int size;
    bool rev;
    ReversibleSplayTreeNode(const T &v=T())
        :l(),r(),p(),val(v),sum(v),size(1),rev(false){}
};

template<class T,T (*combine)(T,T),T (*flip)(T)>
struct ReversibleSplayTree
    : ReversibleBBST<SplayTreeBase<ReversibleSplayTreeNode<T>>,
      ReversibleSplayTreeNode<T>,T,combine,flip>{
    using Node = ReversibleSplayTreeNode<T>;
};