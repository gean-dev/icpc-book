#include <bits/stdc++.h>
#include "../../content/graph/dijkstra.hpp"

using namespace std;

int main(){
    Graph<int,true> g(4);
    g.add(0,1,6);
    g.add(0,2,2);
    g.add(2,1,3);
    g.add(0,2,4);
    auto d=dijkstra(g);
    assert(d[0]==0);
    assert(d[1]==5);
    assert(d[2]==2);
    assert(d[3]==-1);
    cout << "Test Passed!";
}
