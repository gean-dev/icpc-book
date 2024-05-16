#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include "../../content/template/Header.hpp"
#include "../../content/monoid/AffineAddCountAction.hpp"
#include "../../content/modular-arithmetic/MontgomeryModInt.hpp"
#include "../../content/data-structure/SparseSegmentTree.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    using Info = AddCountMonoid<mint>::value_type;
    using Tag = AffineMonoid<mint>::value_type;
    vector<Info> a(n,Info(0,1));
    for(auto &x:a)cin >> x.first;
    SparseSegmentTree<AffineAddCountAction<mint>> seg(n);
    for(int i=0;i<n;i++)seg.modify(i,a[i]);
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