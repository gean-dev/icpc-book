#include "../../content/data-structure/LazyReversibleSplayTree.hpp"
#include "../../content/monoid/AddAddCountAction.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<pair<ll,int>> a(n,pair<ll,int>(0,1));
    for(auto &x:a)cin >> x.first;
    using Tree = LazyReversibleSplayTree<AddAddCountAction<ll>>;
    Tree s;
    using Node = Tree::Node;
    using Ptr = Node*;
    Ptr root=s.build(a);
    while(q--){
        int t,l,r;
        cin >> t >> l >> r;
        r--;
        if(t){
            cout << s.query(root,l,r).first << "\n";
        }else{
            s.reverse(root,l,r);
        }
    }
}