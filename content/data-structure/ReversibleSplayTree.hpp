#pragma once
#include "../template/Header.hpp"
#include "SplayTreeBase.hpp"
#include "ReversibleBBST.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-13
 * Description: Splay Tree. splay(u) will make node u be the root of the tree in amortized O(log n) time.
 */

template<class T>
struct ReversibleSplayTreeNode{
    using Ptr = ReversibleSplayTreeNode*;
    Ptr l,r,p;
    T val,sum,revsum;
    int size;
    bool rev;
    ReversibleSplayTreeNode(const T &_val)
        :l(),r(),p(),val(_val),sum(_val),revsum(_val),size(1),rev(false){}
};

template<class Monoid>
struct ReversibleSplayTree
    : ReversibleBBST<SplayTreeBase<ReversibleSplayTreeNode<typename Monoid::value_type>>,
      ReversibleSplayTreeNode<typename Monoid::value_type>,Monoid>{
    using Node = ReversibleSplayTreeNode<typename Monoid::value_type>;
};

