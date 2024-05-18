#include "../../content/template/Header.hpp"
#include "../../content/modular-arithmetic/MontgomeryModInt.hpp"
#include "../../content/monoid/Affine.hpp"
#include "../../content/data-structure/LinkCutTree.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    using Monoid = AffineMonoid<mint>;
    using T = Monoid::value_type;
    using LCT = LinkCutTree<Monoid>;
    using Node = LCT::Node;
    using Ptr = Node*;
    LCT lct;
    vector<Ptr> ptr(n);
    for(int i=0;i<n;i++){
        int a,b;
        cin >> a >> b;
        ptr[i]=new Node(T(a,b));
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        lct.link(ptr[u],ptr[v]);
    }
    while(q--){
        int op;
        cin >> op;
        if(op==0){
            int u,v,x,y;
            cin >> u >> v >> x >> y;
            lct.cut(ptr[u],ptr[v]);
            lct.link(ptr[x],ptr[y]);
        }else if(op==1){
            int p,c,d;
            cin >> p >> c >> d;
            lct.set_val(ptr[p],T(c,d));
        }else{
            int u,v,x;
            cin >> u >> v >> x;
            cout << Monoid::eval(lct.fold(ptr[u],ptr[v]),x) << "\n";
        }
    }
}