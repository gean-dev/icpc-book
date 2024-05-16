#line 1 "range_affine_range_sum_sparse_segment_tree.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
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

#line 3 "/Users/tata/Desktop/icpc-book/content/monoid/AddCount.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Add & Count Monoid class.
 */

template<class T>
struct AddCountMonoid{
    using P = pair<T,int>;
    using value_type = P;
    static constexpr P op(const P &x,const P &y){
        return P(x.first+y.first,x.second+y.second);
    }
    static constexpr P inverse(const P &x){return P(-x.first,-x.second);}
    static constexpr P unit(){return P(T(0),0);}
    static constexpr P make(const T &x){return P(x,1);}
};

#line 3 "/Users/tata/Desktop/icpc-book/content/monoid/Affine.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Affine Transfomation Monoid class.
 */

template<class T>
struct AffineMonoid{
    using P = pair<T,T>;
    using value_type = P;
    static constexpr P op(const P &x,const P &y){
        return P(x.first*y.first,x.second*y.first+y.second);
    }
    static constexpr P unit(){return P(T(1),T(0));}
    static constexpr T eval(const P &f,const T &x){
        return f.first*x+f.second;
    }
};

#line 5 "/Users/tata/Desktop/icpc-book/content/monoid/AffineAddCountAction.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Affine to Add & Count Action class.
 */

template<class T>
struct AffineAddCountAction{
    using InfoMonoid = AddCountMonoid<T>;
    using TagMonoid = AffineMonoid<T>;
    using Info = typename InfoMonoid::value_type;
    using Tag = typename TagMonoid::value_type;
    static constexpr Info op(const Info &a,const Tag &b){
        return Info(a.first*b.first+a.second*b.second,a.second);
    }
};

#line 3 "/Users/tata/Desktop/icpc-book/content/modular-arithmetic/MontgomeryModInt.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-03-17
 * Description: modular arithmetic operators using Montgomery space
 */

template<uint32_t mod,uint32_t root=0>
struct MontgomeryModInt{
    using mint = MontgomeryModInt;
    using i32 = int32_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

    static constexpr u32 get_r(){
        u32 res=1;
        for(i32 i=0;i<5;i++)res*=2-mod*res;
        return res;
    }

    static const u32 r=get_r();
    static const u32 n2=-u64(mod)%mod;
    static_assert(mod<(1<<30));
    static_assert((mod&1)==1);
    static_assert(r*mod==1);

    u32 x;

    constexpr MontgomeryModInt():x(0){}
    constexpr MontgomeryModInt(const int64_t &v):x(reduce(u64(v%mod+mod)*n2)){}

    static constexpr u32 get_mod(){return mod;}
    static constexpr mint get_root(){return mint(root);}
    explicit constexpr operator ll()const{return val();}

    static constexpr u32 reduce(const u64 &v){
        return (v+u64(u32(v)*u32(-r))*mod)>>32;
    }

    constexpr u32 val()const{
        u32 res=reduce(x);
        return res>=mod?res-mod:res;
    }

    constexpr mint inv()const{
        int a=val(),b=mod,u=1,v=0,q;
        while(b>0){
            q=a/b;
            a-=q*b;
            u-=q*v;
            swap(a,b);
            swap(u,v);
        }
        return mint(u);
    }

    constexpr mint &operator+=(const mint &rhs){
        if(i32(x+=rhs.x-2*mod)<0)x+=2*mod;
        return *this;
    }
    constexpr mint &operator-=(const mint &rhs){
        if(i32(x-=rhs.x)<0)x+=2*mod;
        return *this;
    }
    constexpr mint &operator*=(const mint &rhs){
        x=reduce(u64(x)*rhs.x);
        return *this;
    }
    constexpr mint &operator/=(const mint &rhs){
        return *this*=rhs.inv();
    }

    constexpr mint &operator++(){return *this+=mint(1);}
    constexpr mint &operator--(){return *this-=mint(1);}
    constexpr mint operator++(int){
        mint res=*this;
        return *this+=mint(1),res;
    }
    constexpr mint operator--(int){
        mint res=*this;
        return *this-=mint(1),res;
    }

    constexpr mint operator-()const{return mint()-mint(*this);};
    constexpr mint operator+()const{return mint(*this);};

    friend constexpr mint operator+(const mint &lhs,const mint &rhs){return mint(lhs)+=rhs;}
    friend constexpr mint operator-(const mint &lhs,const mint &rhs){return mint(lhs)-=rhs;}
    friend constexpr mint operator*(const mint &lhs,const mint &rhs){return mint(lhs)*=rhs;}
    friend constexpr mint operator/(const mint &lhs,const mint &rhs){return mint(lhs)/=rhs;}
    friend constexpr bool operator==(const mint &lhs,const mint &rhs){
        return (lhs.x>=mod?lhs.x-mod:lhs.x)==(rhs.x>=mod?rhs.x-mod:rhs.x);
    }
    friend constexpr bool operator!=(const mint &lhs,const mint &rhs){
        return (lhs.x>=mod?lhs.x-mod:lhs.x)!=(rhs.x>=mod?rhs.x-mod:rhs.x);
    }
    friend constexpr bool operator<(const mint &lhs,const mint &rhs){
        return (lhs.x>=mod?lhs.x-mod:lhs.x)<(rhs.x>=mod?rhs.x-mod:rhs.x); // for std::map
    }

    friend istream &operator>>(istream &is,mint &o){
        int64_t v;
        is >> v;
        o=mint(v);
        return is;
    }
    friend ostream &operator<<(ostream &os,const mint &o){
        return os << o.val();
    }
};
using mint = MontgomeryModInt<MOD,3>;
using vm = vector<mint>;

#line 3 "/Users/tata/Desktop/icpc-book/content/data-structure/SparseSegmentTree.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-01-15
 * Description: Sparse Segment Tree
 */

template<class MonoidAction>
struct SparseSegmentTree{
    using InfoMonoid = typename MonoidAction::InfoMonoid;
    using TagMonoid = typename MonoidAction::TagMonoid;
    using Info = typename MonoidAction::Info;
    using Tag = typename MonoidAction::Tag;
    struct Node;
    using Ptr = Node*;
    struct Node{
        Info val;
        Tag lz;
        Ptr l,r;
        Node():val(InfoMonoid::unit()),lz(TagMonoid::unit()),l(nullptr),r(nullptr){}
        Node(Info v,Tag t):val(v),lz(t),l(nullptr),r(nullptr){}
    };
    ll lb,ub;
    Ptr rt;
    SparseSegmentTree(){}
    SparseSegmentTree(ll n){init(0,n-1);}
    SparseSegmentTree(ll lb,ll ub){init(lb,ub);}
    void init(ll _lb,ll _ub){
        lb=_lb,ub=_ub,rt=new Node();
    }
    Info val(Ptr t){
        return t?t->val:InfoMonoid::unit();
    }
    void pull(Ptr &t){
        t->val=InfoMonoid::op(val(t->l),val(t->r));
    }
    void apply(Ptr &t,const Tag &v){
        if(!t)t=new Node();
        t->val=MonoidAction::op(t->val,v);
        t->lz=TagMonoid::op(t->lz,v);
    }
    void push(Ptr &t){
        apply(t->l,t->lz);
        apply(t->r,t->lz);
        t->lz=TagMonoid::unit();
    }
    void modify(ll l,ll r,Ptr &t,ll x,const Info &v){
        if(x<l||r<x)return;
        if(l==r)return void(t->val=v);
        ll m=l+(r-l)/2;
        push(t);
        modify(l,m,t->l,x,v);
        modify(m+1,r,t->r,x,v);
        pull(t);
    }
    void modify(ll x,const Info &v){
        modify(lb,ub,rt,x,v);
    }
    void update(ll l,ll r,Ptr &t,ll x,ll y,const Tag &v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(t,v);
        ll m=l+(r-l)/2;
        push(t);
        update(l,m,t->l,x,y,v);
        update(m+1,r,t->r,x,y,v);
        pull(t);
    }
    void update(ll x,ll y,const Tag &v){
        update(lb,ub,rt,x,y,v);
    }
    Info query(ll l,ll r,Ptr &t,ll x,ll y){
        if(y<l||r<x)return InfoMonoid::unit();
        if(x<=l&&r<=y)return t->val;
        ll m=l+(r-l)/2;
        push(t);
        return InfoMonoid::op(query(l,m,t->l,x,y),query(m+1,r,t->r,x,y));
    }
    Info query(ll x,ll y){
        return query(lb,ub,rt,x,y);
    }
    template<class F>
    ll findfirst(ll l,ll r,Ptr t,ll x,ll y,const F &f){
        if(y<l||r<x||!f(t->val))return -1;
        if(l==r)return l;
        ll m=l+(r-l)/2;
        push(t);
        ll res=findfirst(l,m,t->l,x,y,f);
        if(res==-1)res=findfirst(m+1,r,t->r,x,y,f);
        return res;
    }
    template<class F>
    ll findfirst(ll x,ll y,const F &f){
        return findfirst(lb,ub,rt,x,y,f);
    }
    template<class F>
    ll findlast(ll l,ll r,Ptr t,ll x,ll y,const F &f){
        if(y<l||r<x||!t||!f(t->val))return -1;
        if(l==r)return l;
        ll m=l+(r-l)/2;
        push(t);
        ll res=findlast(m+1,r,t->r,x,y,f);
        if(res==-1)res=findlast(l,m,t->l,x,y,f);
        return res;
    }
    template<class F>
    ll findlast(ll x,ll y,const F &f){
        return findlast(lb,ub,rt,x,y,f);
    }
};
struct AddTag{
    ll val;
    AddTag():val(0){}
    AddTag(ll v):val(v){}
    void apply(ll l,ll r,const AddTag &v){
        val+=v.val;
    }
};
struct MaxNode{
    ll val;
    MaxNode():val(-LINF){}
    MaxNode(ll x):val(x){}
    void apply(ll l,ll r,const AddTag &v){
        val+=v.val;
    }
    friend MaxNode operator+(const MaxNode &lhs,const MaxNode &rhs){
        return MaxNode(max(lhs.val,rhs.val));
    }
};
struct MinNode{
    ll val;
    MinNode():val(LINF){}
    MinNode(ll v):val(v){}
    void apply(ll l,ll r,const AddTag &v){
        val+=v.val;
    }
    friend MinNode operator+(const MinNode &lhs,const MinNode &rhs){
        return MinNode(min(lhs.val,rhs.val));
    }
};
struct SumNode{
    ll val;
    SumNode():val(0){}
    SumNode(ll v):val(v){}
    void apply(ll l,ll r,const AddTag &v){
        val+=v.val*(r-l+1);
    }
    friend SumNode operator+(const SumNode &lhs,const SumNode &rhs){
        return SumNode(lhs.val+rhs.val);
    }
};

#line 6 "range_affine_range_sum_sparse_segment_tree.cpp"

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
