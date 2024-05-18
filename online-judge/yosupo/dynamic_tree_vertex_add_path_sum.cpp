#include "../../content/template/Header.hpp"
#include "../../content/monoid/Add.hpp"
#include "../../content/data-structure/LinkCutTree.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    using LCT = LinkCutTree<AddMonoid<ll>>;
    using Node = LCT::Node;
    using Ptr = Node*;
    int n,q;
    cin >> n >> q;
    LCT lct;
    vector<ll> a(n);
    vector<Ptr> ptr(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        ptr[i]=new Node(a[i]);
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
            int p,v;
            cin >> p >> v;
            a[p]+=v;
            lct.set_val(ptr[p],a[p]);
        }else{
            int u,v;
            cin >> u >> v;
            cout << lct.fold(ptr[u],ptr[v]) << "\n";
        }
    }
}