#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../../content/template/Header.hpp"
#include "../../content/monoid/add.hpp"
#include "../../content/monoid/DefaultAction.hpp"
#include "../../content/data-structure/LazySegmentTree.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<ll> a(n);
    for(auto &x:a)cin>>x;
    LazySegmentTree<DefaultAction<AddMonoid<ll>>> seg(a);
    while(q--){
        int t;
        cin>>t;
        if(t==0){
            int p,x;
            cin>>p>>x;
            seg.update(p,p,x);
        }else{
            int l,r;
            cin >> l >> r;
            r--;
            cout << seg.query(l,r) << "\n";
        }
    }
}