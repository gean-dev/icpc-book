#line 2 "/Users/tata/Desktop/icpc-book/content/template/Header.hpp"
#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdd = pair<db, db>;
const int INF = 0x3fffffff;
// const int MOD=1000000007;
const int MOD = 998244353;
const ll LINF = 0x1fffffffffffffff;
const db DINF = numeric_limits<db>::infinity();
const db EPS = 1e-9;
const db PI = acos(db(-1));

#line 3 "/Users/tata/Desktop/icpc-book/content/monoid/Add.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Add Monoid class.
 */

template<class T>
struct AddMonoid{
    using value_type = T;
    static constexpr T op(const T &x,const T &y){return x+y;}
    static constexpr T inverse(const T &x){return -x;}
    static constexpr T unit(){return T(0);}
};

#line 3 "/Users/tata/Desktop/icpc-book/content/data-structure/SplayTreeBase.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-13
 * Description: Splay Tree. splay(u) will make node u be the root of the tree in amortized O(log n) time.
 */

template<class Node>
struct SplayTreeBase{
    using Ptr = Node*;
    bool is_root(Ptr t){
        return !(t->p)||(t->p->l!=t&&t->p->r!=t);
    } // The parent of the root stores the path parant in link cut tree.
    int size(Ptr t){
        return t?t->size:0;
    }
    virtual void push(Ptr t){};
    virtual void pull(Ptr t){};
    int pos(Ptr t){
        if(t->p){
            if(t->p->l==t)return -1;
            if(t->p->r==t)return 1;
        }
        return 0;
    }
    void rotate(Ptr t){
        Ptr x=t->p,y=x->p;
        if(pos(t)==-1){
            if((x->l=t->r))t->r->p=x;
            t->r=x,x->p=t;
        }else{
            if((x->r=t->l))t->l->p=x;
            t->l=x,x->p=t;
        }
        pull(x),pull(t);
        if((t->p=y)){
            if(y->l==x)y->l=t;
            if(y->r==x)y->r=t;
        }
    }
    void splay(Ptr t){
        if(!t)return;
        push(t);
        while(!is_root(t)){
            Ptr x=t->p;
            if(is_root(x)){
                push(x),push(t);
                rotate(t);
            }else{
                Ptr y=x->p;
                push(y),push(x),push(t);
                if(pos(x)==pos(t))rotate(x),rotate(t);
                else rotate(t),rotate(t);
            }
        }
    }
    Ptr get_first(Ptr t){
        while(t->l)push(t),t=t->l;
        splay(t);
        return t;
    }
    Ptr get_last(Ptr t){
        while(t->r)push(t),t=t->r;
        splay(t);
        return t;
    }
    Ptr merge(Ptr l,Ptr r){
        splay(l),splay(r);
        if(!l)return r;
        if(!r)return l;
        l=get_last(l);
        l->r=r;
        r->p=l;
        pull(l);
        return l;
    }
    pair<Ptr,Ptr> split(Ptr t,int k){
        if(!t)return {nullptr,nullptr};
        if(k==0)return {nullptr,t};
        if(k==size(t))return {t,nullptr};
        push(t);
        if(k<=size(t->l)){
            auto x=split(t->l,k);
            t->l=x.second;
            t->p=nullptr;
            if(x.second)x.second->p=t;
            pull(t);
            return {x.first,t};
        }else{
            auto x=split(t->r,k-size(t->l)-1);
            t->r=x.first;
            t->p=nullptr;
            if(x.first)x.first->p=t;
            pull(t);
            return {t,x.second};
        }
    }
    void insert(Ptr &t,int k,Ptr v){
        splay(t);
        auto x=split(t,k);
        t=merge(merge(x.first,v),x.second);
    }
    void erase(Ptr &t,int k){
        splay(t);
        auto x=split(t,k);
        auto y=split(x.second,1);
        // delete y.first;
        t=merge(x.first,y.second);
    }
    template<class T>
    Ptr build(const vector<T> &v){
        if(v.empty())return nullptr;
        function<Ptr(int,int)> build=[&](int l,int r){
            if(l==r)return new Node(v[l]);
            int m=(l+r)/2;
            return merge(build(l,m),build(m+1,r));
        };
        return build(0,v.size()-1);
    }
};

#line 3 "/Users/tata/Desktop/icpc-book/content/data-structure/ReversibleBBST.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-13
 * Description: template for revesible BBST.
 */

template<class Tree,class Node,class Monoid>
struct ReversibleBBST:Tree{
    using Tree::merge;
    using Tree::split;
    using typename Tree::Ptr;
    using T = typename Monoid::value_type;

    ReversibleBBST()=default;

    T sum(Ptr t){
        return t?t->sum:T();
    }
    void pull(Ptr t){
        if(!t)return;
        t->size=1;
        t->sum=t->val;
        t->revsum=t->val;
        if(t->l){
            t->size+=t->l->size;
            t->sum=Monoid::op(t->l->sum,t->sum);
            t->revsum=Monoid::op(t->revsum,t->l->revsum);
        }
        if(t->r){
            t->size+=t->r->size;
            t->sum=Monoid::op(t->sum,t->r->sum);
            t->revsum=Monoid::op(t->r->revsum,t->revsum);
        }
    }
    void push(Ptr t){
        if(!t)return;
        if(t->rev){
            toggle(t->l);
            toggle(t->r);
            t->rev=false;
        }
    }
    void toggle(Ptr t){
        if(!t)return;
        swap(t->l,t->r);
        swap(t->sum,t->revsum);
        t->rev^=true;
    }
    T query(Ptr &t,int l,int r){
        if(l>r)return T();
        auto x=split(t,l);
        auto y=split(x.second,r-l+1);
        T res=sum(y.first);
        t=merge(x.first,merge(y.first,y.second));
        return res;
    }
    void reverse(Ptr &t,int l,int r){
        if(l>r)return;
        auto x=split(t,l);
        auto y=split(x.second,r-l+1);
        toggle(y.first);
        t=merge(x.first,merge(y.first,y.second));
    }
};

#line 5 "/Users/tata/Desktop/icpc-book/content/data-structure/ReversibleSplayTree.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-13
 * Description: Splay Tree. splay(u) will make node u be the root of the tree in amortized O(log n) time.
 */

template<class T>
struct ReversibleSplayTreeNode{
    using Ptr = ReversibleSplayTreeNode*;
	using value_type = T;
    Ptr l,r,p;
    T val,sum,revsum;
    int size;
    bool rev;
    ReversibleSplayTreeNode(const T &_val)
        :l(),r(),p(),val(_val),sum(_val),revsum(_val),size(1),rev(false){}
};

template<class Monoid>
struct ReversibleSplayTree
    : ReversibleBBST<SplayTreeBase<ReversibleSplayTreeNode<typename Monoid::value_type>>,
      ReversibleSplayTreeNode<typename Monoid::value_type>,Monoid>{
    using Node = ReversibleSplayTreeNode<typename Monoid::value_type>;
};

#line 3 "/Users/tata/Desktop/icpc-book/content/data-structure/LinkCutTreeBase.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-05-19
 * Description: Link Cut Tree Base.
 * Usage:
 *  evert(u): make u be the root of the tree.
 *  link(u,v): attach u to v.
 *  cut(u,v): remove edge between u and v.
 *  get_root(u): get the root of the tree containing u.
 *  lca(u,v): get the lowest common ancestor of u and v.
 *  fold(u,v): get the value of the path from u to v.
 */

template<class Splay>
struct LinkCutTreeBase:Splay{
    using Node = typename Splay::Node;
    using Ptr = Node*;
    using T = typename Node::value_type;
    Ptr expose(Ptr t){
        Ptr pc=nullptr; // preferred child
        for(Ptr cur=t;cur;cur=cur->p){
            this->splay(cur);
            cur->r=pc;
            this->pull(cur);
            pc=cur;
        }
        this->splay(t);
        return pc;
    }
    void evert(Ptr t){ // make t be the root of the tree
        expose(t);
        this->toggle(t);
        this->push(t);
    }
    void link(Ptr u,Ptr v){ // attach u to v
        evert(u);
        expose(v);
        u->p=v;
    }
    void cut(Ptr u,Ptr v){
        evert(u);
        expose(v);
        assert(u->p==v);
        v->l=u->p=nullptr;
        this->pull(v);
    }
    Ptr get_root(Ptr t){
        expose(t);
        while(t->l)this->push(t),t=t->l;
        this->splay(t);
        return t;
    }
    Ptr lca(Ptr u,Ptr v){
        if(get_root(u)!=get_root(v))return nullptr;
        expose(u);
        return expose(v);
    }
    void set_val(Ptr t,const T &val){
        this->evert(t);
        t->val=val;
        this->pull(t);
    }
    T get_val(Ptr t){
        this->evert(t);
        return t->val;
    }
    T fold(Ptr u,Ptr v){
        evert(u);
        expose(v);
        return v->sum;
    }
};

#line 4 "/Users/tata/Desktop/icpc-book/content/data-structure/LinkCutTree.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-05-19
 * Description: Link Cut Tree.
 */

template<class Monoid>
struct LinkCutTree:LinkCutTreeBase<ReversibleSplayTree<Monoid>>{};

#line 4 "dynamic_tree_vertex_add_path_sum.cpp"

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
