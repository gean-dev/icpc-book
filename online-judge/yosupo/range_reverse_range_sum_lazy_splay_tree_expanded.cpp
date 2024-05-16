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

#line 3 "/Users/tata/Desktop/icpc-book/content/monoid/add.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Add Monoid class.
 */

template<typename T>
struct AddMonoid{
    using value_type = T;
    constexpr T operator()(const T &x,const T &y){return x+y;}
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
            if(x->l=t->r)t->r->p=x;
            t->r=x,x->p=t;
        }else{
            if(x->r=t->l)t->l->p=x;
            t->l=x,x->p=t;
        }
        pull(x),pull(t);
        if(t->p=y){
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
        return t;
    }
    Ptr get_last(Ptr t){
        while(t->r)push(t),t=t->r;
        return t;
    }
    Ptr merge(Ptr l,Ptr r){
        splay(l),splay(r);
        if(!l)return r;
        if(!r)return l;
        l=get_last(l);
        splay(l);
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
        delete y.first;
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

#line 3 "/Users/tata/Desktop/icpc-book/content/data-structure/LazyReversibleBBST.hpp"

/**
 * Author: Teetat Info.
 * Date: 2024-04-13
 * Description: template for revesible BBST.
 */

template<typename Tree,typename Node,typename MonoidAction>
struct LazyReversibleBBST:Tree{
    using Tree::merge;
    using Tree::split;
    using typename Tree::Ptr;
    using Act = MonoidAction;
    using MInfo = typename Act::MonoidA;
    using MTag = typename Act::MonoidB;
    using Info = typename Act::A;
    using Tag = typename Act::B;

    LazyReversibleBBST()=default;

    Info sum(Ptr t){
        return t?t->sum:Info();
    }
    void pull(Ptr t){
        if(!t)return;
        t->size=1;
        t->sum=t->val;
        t->revsum=t->val;
        if(t->l){
            t->size+=t->l->size;
            t->sum=MInfo()(t->l->sum,t->sum);
            t->revsum=MInfo()(t->revsum,t->l->revsum);
        }
        if(t->r){
            t->size+=t->r->size;
            t->sum=MInfo()(t->sum,t->r->sum);
            t->revsum=MInfo()(t->r->revsum,t->revsum);
        }
    }
    void push(Ptr t){
        if(!t)return;
        if(t->rev){
            toggle(t->l);
            toggle(t->r);
            t->rev=false;
        }
        if(t->lz!=MTag::unit()){
            propagate(t->l,t->lz);
            propagate(t->r,t->lz);
            t->lz=MTag::unit();
        }
    }
    void toggle(Ptr t){
        if(!t)return;
        swap(t->l,t->r);
        swap(t->sum,t->revsum);
        t->rev^=true;
    }
    void propagate(Ptr t,const Tag &v){
        t->val=Act()(t->val,v);
        t->sum=Act()(t->sum,v);
        t->revsum=Act()(t->revsum,v);
        t->lz=MTag()(t->lz,v);
    }
    void apply(Ptr &t,int l,int r,const Tag &v){
        if(l>r)return;
        auto x=split(t,l);
        auto y=split(x.second,r-l+1);
        propagate(y.first,v);
        t=merge(x.first,merge(y.first,y.second));
    }
    Info query(Ptr &t,int l,int r){
        if(l>r)return Info();
        auto x=split(t,l);
        auto y=split(x.second,r-l+1);
        Info res=sum(y.first);
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

#line 5 "/Users/tata/Desktop/icpc-book/content/data-structure/LazyReversibleSplayTree.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-13
 * Description: Splay Tree. splay(u) will make node u be the root of the tree in amortized O(log n) time.
 */

template<typename MonoidAction>
struct LazyReversibleSplayTreeNode{
    using Ptr = LazyReversibleSplayTreeNode*;
    using MInfo = typename MonoidAction::MonoidA;
    using MTag = typename MonoidAction::MonoidB;
    using Info = typename MonoidAction::A;
    using Tag = typename MonoidAction::B;
    Ptr l,r,p;
    Info val,sum,revsum;
    Tag lz;
    int size;
    bool rev;
    LazyReversibleSplayTreeNode(const Info &_val=MInfo::unit(),const Tag &_lz=MTag::unit())
        :l(),r(),p(),val(_val),sum(_val),revsum(_val),lz(_lz),size(1),rev(false){}
};

template<typename MonoidAction>
struct LazyReversibleSplayTree
    : LazyReversibleBBST<SplayTreeBase<LazyReversibleSplayTreeNode<MonoidAction>>,
      LazyReversibleSplayTreeNode<MonoidAction>,MonoidAction>{
    using Node = LazyReversibleSplayTreeNode<MonoidAction>;
};

#line 3 "/Users/tata/Desktop/icpc-book/content/monoid/add-count.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Add & Count Monoid class.
 */

template<typename T>
struct AddCountMonoid{
    using P = pair<T,int>;
    using value_type = P;
    constexpr P operator()(const P &x,const P &y){
        return P(x.first+y.first,x.second+y.second);
    }
    static constexpr P inverse(const P &x){return P(-x.first,-x.second);}
    static constexpr P unit(){return P(T(0),0);}
    static constexpr P make(const T &x){return P(x,1);}
};

#line 5 "/Users/tata/Desktop/icpc-book/content/monoid/add-add-count-action.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Add to Add & Count Monoid class.
 */

template<typename T>
struct AddAddCountAction{
    using MonoidA = AddCountMonoid<T>;
    using MonoidB = AddMonoid<T>;
    using A = typename MonoidA::value_type;
    using B = typename MonoidB::value_type;
    constexpr A operator()(const A &a,const B &b){
        return A(a.first+a.second*b,a.second);
    }
};

#line 4 "range_reverse_range_sum_lazy_splay_tree.cpp"

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
