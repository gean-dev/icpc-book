#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class Node,class Tag>
struct DynamicSegTree{
    struct node;
    using pnode = node*;
    struct node{
        Node val;
        Tag lz;
        pnode l,r;
        node():val(Node()),lz(Tag()),l(nullptr),r(nullptr){}
        node(Node v,Tag t):val(v),lz(t),l(nullptr),r(nullptr){}
    };
    ll n;
    pnode rt;
    DynamicSegTree(){}
    DynamicSegTree(ll n){init(n);}
    void init(ll _n){
        n=_n,rt=new node();
    }
    Node val(pnode t){
        return t?t->val:Node();
    }
    void pull(pnode &t){
        t->val=val(t->l)+val(t->r);
    }
    void apply(ll l,ll r,pnode &t,const Tag &v){
        if(!t)t=new node();
        t->val.apply(l,r,v);
        t->lz.apply(l,r,v);
    }
    void push(ll l,ll r,pnode &t){
        ll m=(l+r)/2;
        apply(l,m,t->l,t->lz);
        apply(m+1,r,t->r,t->lz);
        t->lz=Tag();
    }
    void modify(ll l,ll r,pnode &t,ll x,const Node &v){
        if(x<l||r<x)return;
        if(l==r)return void(t->val=v);
        ll m=(l+r)/2;
        push(l,r,t);
        modify(l,m,t->l,x,v);
        modify(m+1,r,t->r,x,v);
        pull(t);
    }
    void modify(ll x,const Node &v){
        modify(0,n-1,rt,x,v);
    }
    void update(ll l,ll r,pnode &t,ll x,ll y,const Tag &v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(l,r,t,v);
        ll m=(l+r)/2;
        push(l,r,t);
        update(l,m,t->l,x,y,v);
        update(m+1,r,t->r,x,y,v);
        pull(t);
    }
    void update(ll x,ll y,const Tag &v){
        update(0,n-1,rt,x,y,v);
    }
    Node query(ll l,ll r,pnode &t,ll x,ll y){
        if(y<l||r<x)return Node();
        if(x<=l&&r<=y)return t->val;
        ll m=(l+r)/2;
        push(l,r,t);
        return query(l,m,t->l,x,y)+query(m+1,r,t->r,x,y);
    }
    Node query(ll x,ll y){
        return query(0,n-1,rt,x,y);
    }
    template<class F>
    ll findfirst(ll l,ll r,pnode t,ll x,ll y,const F &f){
        if(y<l||r<x||!f(t->val))return -1;
        if(l==r)return l;
        ll m=(l+r)/2;
        push(l,r,t);
        ll res=findfirst(l,m,t->l,x,y,f);
        if(res==-1)res=findfirst(m+1,r,t->r,x,y,f);
        return res;
    }
    template<class F>
    ll findfirst(ll x,ll y,const F &f){
        return findfirst(0,n-1,rt,x,y,f);
    }
    template<class F>
    ll findlast(ll l,ll r,pnode t,ll x,ll y,const F &f){
        if(y<l||r<x||!t||!f(t->val))return -1;
        if(l==r)return l;
        ll m=(l+r)/2;
        push(l,r,t);
        ll res=findlast(m+1,r,t->r,x,y,f);
        if(res==-1)res=findlast(l,m,t->l,x,y,f);
        return res;
    }
    template<class F>
    ll findlast(ll x,ll y,const F &f){
        return findlast(0,n-1,rt,x,y,f);
    }
};
struct Tag{
    ll add,mod;
    bool ok;
    Tag():add(0),mod(0),ok(false){}
    Tag(ll _add,ll _mod,bool _ok):add(_add),mod(_mod),ok(_ok){}
    void apply(int l,int r,const Tag &v){
        if(v.ok){
            mod=v.mod;
            ok=true;
        }else if(ok){
            mod+=v.add;
        }else{
            add+=v.add;
        }
    }
};
struct SumNode{
    ll val;
    SumNode(ll v=0):val(v){}
    void apply(int l,int r,const Tag &v){
        ll sz=r-l+1;
        if(v.ok){
            val=v.mod*sz;
        }else{
            val+=v.add*sz;
        }
    }
    friend SumNode operator+(const SumNode &lhs,const SumNode &rhs){
        return SumNode(lhs.val+rhs.val);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vl a(n);
    for(auto &x:a)cin >> x;
    DynamicSegTree<SumNode,Tag> s(n);
    for(int i=0;i<n;i++)s.modify(i,a[i]);
    while(q--){
        int t,l,r;
        cin >> t >> l >> r;
        l--,r--;
        if(t==3){
            cout << s.query(l,r).val << "\n";
        }else{
            ll v;
            cin >> v;
            if(t==1)s.update(l,r,Tag(v,0,false));
            else s.update(l,r,Tag(0,v,true));
        }
    }
}