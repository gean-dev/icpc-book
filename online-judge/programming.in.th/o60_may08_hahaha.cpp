#include "template/Header.hpp"
#include "monoid/set.hpp"
#include "data-structure/LazyReversibleSplayTree.hpp"

struct Info{
    array<ll,5> freq;
    ll val;
    Info(){
        for(int i=0;i<5;i++)freq[i]=0;
        val=0;
    }
    Info(int x){
        for(int i=0;i<5;i++)freq[i]=(i==x);
        val=0;
    }
};

struct Inversion{
    using T = Info;
    using value_type = T;
    T operator()(const T &a,const T &b){
        T c;
        ll cnt=0;
        c.val=a.val+b.val;
        for(int i=0;i<5;i++){
            c.freq[i]=a.freq[i]+b.freq[i];
            c.val+=a.freq[i]*cnt;
            cnt+=b.freq[i];
        }
        return c;
    }
    static T unit(){return T();}
};

struct MonoidAction{
    using MonoidA = Inversion;
    using MonoidB = SetMonoid<int>;
    using A = typename MonoidA::value_type;
    using B = typename MonoidB::value_type;
    A operator()(const A &a,const B &b){
        if(!b.second)return a;
        A c;
        for(int i=0;i<5;i++)c.freq[b.first]+=a.freq[i];
        return c;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<Info> a;
    for(int i=0;i<n;i++){
        char c;
        cin >> c;
        a.emplace_back(Info(int(c-'0')));
    }
    using Tree = LazyReversibleSplayTree<MonoidAction>;
    using Node = Tree::Node;
    using Ptr = Node*;
    Tree s;
    Ptr root=s.build(a);
    while(q--){
        int t,a,b;
        cin >> t >> a >> b;
        a--,b--;
        if(t==1){
            int c;
            cin >> c;
            s.apply(root,a,b,SetMonoid<int>::make(c));
        }else if(t==2){
            s.reverse(root,a,b);
        }else{
            cout << s.query(root,a,b).val << "\n";
        }
    }
}