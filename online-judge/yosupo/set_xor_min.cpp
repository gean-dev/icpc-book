#include "../../content/various/BinaryTrie.hpp"

signed main(int argc, char *argv[]) {
  cin.tie(nullptr)->ios::sync_with_stdio(false);
  int q;
  cin >> q;
  binary_trie<30> t;
  set<int> st;
  while(q--) {
    int opr, x;
    cin >> opr >> x;
    if(opr == 0) {
      if(st.count(x)) {
        continue;
      }
      st.emplace(x);
      t.insert(x);
    }
    else if(opr == 1) {
      if(!st.count(x)) {
        continue;
      }
      st.erase(x);
      t.remove(x);
    }
    else {
      cout << t.get_min(x) << "\n";
    }
  }
  return 0;
}