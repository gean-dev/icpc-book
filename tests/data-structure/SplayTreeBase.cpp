#include "../../content/template/Header.hpp"
#include "../../content/data-structure/ReversibleSplayTree.hpp"
#include "../../content/monoid/Add.hpp"

using namespace std;

int main(){
    vector<ll> a{1,2,3,4};
    using Tree = ReversibleSplayTree<AddMonoid<ll>>;
    Tree s;
    using Node = Tree::Node;
    using Ptr = Node*;
    Ptr root=s.build(a);
    assert(s.query(root,1,2)==5);
    s.reverse(root,2,3);
    assert(s.query(root,0,2)==7);
    s.reverse(root,4,3);
    assert(s.query(root,0,-1)==0);
    cout << "Test Passed!";
}