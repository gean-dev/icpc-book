#include "../../content/data-structure/ReversibleSplayTree.hpp";

using namespace std;

ll combine(ll l,ll r){
    return l+r;
}

ll flip(ll x){
    return x;
}

int main(){
    vector<ll> a{1,2,3,4};
    ReversibleSplayTree<ll,combine,flip> s;
    using Node = ReversibleSplayTree<ll,combine,flip>::Node;
    using Ptr = Node*;
    Ptr root=s.build(a);
    assert(s.query(root,1,2)==5);
    s.reverse(root,2,3);
    assert(s.query(root,0,2)==7);
    s.reverse(root,4,3);
    assert(s.query(root,0,-1)==0);
    cout << "Test Passed!";
}