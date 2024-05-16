#include "../../content/monoid/Add.hpp"
#include "../../content/data-structure/ReversibleSplayTree.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    using Tree = ReversibleSplayTree<AddMonoid<ll>>;
    Tree s;
    using Node = Tree::Node;
    using Ptr = Node*;
    Ptr root=s.build(a);
    while(q--){
        int t,l,r;
        cin >> t >> l >> r;
        r--;
        if(t){
            cout << s.query(root,l,r) << "\n";
        }else{
            s.reverse(root,l,r);
        }
    }
}