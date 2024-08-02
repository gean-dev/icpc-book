#pragma once
#include "../template/Header.hpp"

/**
 * Author: Borworntat D.
 * Date: 2024-08-02
 * License: CC0
 * Description: Ordered Set
 */

#include <bits/extc++.h>
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// can be change to less_equal

void usage() {
  ordered_set<int> st, st_2;
  st.insert(2);
  st.insert(1);
  cout << st.order_of_key(2);
  cout << *st.find_by_order(1);
  st.join(st_2); // merge
}