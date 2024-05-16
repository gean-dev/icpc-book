#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include "../../template/Header.hpp"
#include "../../monoid/AffineAddCountAction.hpp"
#include "../../modular-arithmetic/MontgomeryModInt.hpp"
#include "../../data-structure/LazySegmentTree.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    using Info = AddCountMonoid<mint>::value_type;
    using Tag = AffineMonoid<mint>::value_type;
    vector<Info> a(n,Info(0,1));
    for(auto &x:a)cin >> x.first;
    LazySegmentTree<AffineAddCountAction<mint>> seg(a);
    while(q--){
        int t;
        cin >> t;
        if(t==0){
            int l,r,b,c;
            cin >> l >> r >> b >> c;
            r--;
            seg.update(l,r,Tag(b,c));
        }else{
            int l,r;
            cin >> l >> r;
            r--;
            cout << seg.query(l,r).first << "\n";
        }
    }
}