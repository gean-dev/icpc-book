#pragma once
#include "SplayTreeBase.hpp"
#include "ReversibleBBST.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-13
 * Description: Reversible Splay Tree.
 */

template<class T>
struct ReversibleSplayTreeNode{
    using Ptr = ReversibleSplayTreeNode*;
	using value_type = T;
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

