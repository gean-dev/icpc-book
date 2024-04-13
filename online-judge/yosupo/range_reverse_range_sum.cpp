#include<bits/stdc++.h>

using namespace std;

using ll = long long;

template<class Node>
struct SplayTreeBase{
    using Ptr = Node*;
    bool is_root(Ptr t){
        return !(t->p)||(t->p->l!=t&&t->p->r!=t);
    }
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
        auto y=x.split(x.second,1);
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

template<class Tree,class Node,class T,T (*combine)(T,T),T (*flip)(T)>
struct ReversibleBBST:Tree{
    using Tree::merge;
    using Tree::split;
    using Ptr = Node*;

    ReversibleBBST()=default;

    T sum(Ptr t){
        return t?t->sum:T();
    }
    void pull(Ptr t){
        if(!t)return;
        t->size=1;
        t->sum=t->val;
        if(t->l)t->size+=t->l->size,t->sum=combine(t->l->sum,t->sum);
        if(t->r)t->size+=t->r->size,t->sum=combine(t->sum,t->r->sum);
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
        t->sum=flip(t->sum);
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

template<class T>
struct ReversibleSplayTreeNode{
    using Ptr = ReversibleSplayTreeNode*;
    Ptr l,r,p;
    T val,sum;
    int size;
    bool rev;
    ReversibleSplayTreeNode(const T &v=T())
        :l(),r(),p(),val(v),sum(v),size(1),rev(false){}
};

template<class T,T (*combine)(T,T),T (*flip)(T)>
struct ReversibleSplayTree
    : ReversibleBBST<SplayTreeBase<ReversibleSplayTreeNode<T>>,
      ReversibleSplayTreeNode<T>,T,combine,flip>{
    using Node = ReversibleSplayTreeNode<T>;
};

ll combine(ll l,ll r){
    return l+r;
}

ll flip(ll x){
    return x;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    ReversibleSplayTree<ll,combine,flip> s;
    using Node = ReversibleSplayTree<ll,combine,flip>::Node;
    using Ptr = Node*;
    Ptr root=s.build(a);
    while(q--){
        int t,l,r;
        cin >> t >> l >> r;
        r--;
        if(t){
            cout << s.query(root,l,r) << "\n";
        }else{
            s.reverse(root,l,r);
        }
    }
}