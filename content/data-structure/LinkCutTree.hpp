#pragma once
#include "ReversibleSplayTree.hpp"
#include "LinkCutTreeBase.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-05-19
 * Description: Link Cut Tree.
 */

template<class Monoid>
struct LinkCutTree:LinkCutTreeBase<ReversibleSplayTree<Monoid>>{};

