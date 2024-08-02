#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"
#include "template/Header.hpp"
#include "modular-arithmetic/MontgomeryModInt.hpp"
#include "monoid/AffineAddCountAction.hpp"
#include "data-structure/LazyReversibleSplayTree.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    using Info = AddCountMonoid<mint>::value_type;
    using Tag = AffineMonoid<mint>::value_type;
    vector<Info> a(n,Info(0,1));
    for(auto &x:a)cin >> x.first;
    using Tree = LazyReversibleSplayTree<AffineAddCountAction<mint>>;
    using Node = Tree::Node;
    using Ptr = Node*;
    Tree splay;
    Ptr root=splay.build(a);
    while(q--){
        int t;
        cin >> t;
        if(t==0){
            int i,x;
            cin >> i >> x;
            splay.insert(root,i,new Node(Info(x,1)));
        }else if(t==1){
            int i;
            cin >> i;
            splay.erase(root,i);
        }else if(t==2){
            int l,r;
            cin >> l >> r;
            r--;
            splay.reverse(root,l,r);
        }else if(t==3){
            int l,r,b,c;
            cin >> l >> r >> b >> c;
            r--;
            splay.apply(root,l,r,Tag(b,c));
        }else if(t==4){
            int l,r;
            cin >> l >> r;
            r--;
            cout << splay.query(root,l,r).first << "\n";
        }
    }
}