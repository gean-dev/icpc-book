#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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

template<class T>
struct Edge{
    int from,to;
    T cost;
    Edge(int _to,T _cost):from(-1),to(_to),cost(_cost){}
    Edge(int _from,int _to,T _cost):from(_from),to(_to),cost(_cost){}
    Edge &operator=(const int &x){
        to=x;
        return *this;
    }
    operator int()const{
        return to;
    }
};

template<class T=int,bool directed=false>
struct Graph{
    static constexpr bool is_directed=directed;
    using cost_t = T;
    using edge_t = Edge<T>;
    int n,m;
    vector<edge_t> edges;
    vector<vector<edge_t>> adj;
    vector<int> deg,indeg,outdeg;
    Graph(int _n=0){
        init(_n);
    }
    void init(int _n){
        n=_n,m=0;
        edges.clear();
        adj.assign(n,vector<edge_t>{});
    }
    void add(int from,int to,T cost=1){
        assert(0<=from&&from<n&&0<=to&&to<n);
        edges.emplace_back(edge_t(from,to,cost));
        adj[from].emplace_back(edge_t(from,to,cost));
        if(!directed)adj[to].emplace_back(edge_t(to,from,cost));
        m++;
    }
    void read(int _m,bool weighted=false,int offset=1){
        for(int i=0;i<_m;i++){
            int u,v;
            cin >> u >> v;
            u-=offset,v-=offset;
            if(weighted){
                T w;
                cin >> w;
                add(u,v,w);
            }else{
                add(u,v);
            }
        }
    }
    void calc_deg(){
        if(!deg.empty())return;
        deg.assign(n,0);
        for(auto &&e:edges)deg[e.from]++,deg[e.to]++;
    }
    void calc_deginout(){
        if(!indeg.empty()||!outdeg.empty())return;
        indeg.assign(n,0),outdeg.assign(n,0);
        for(auto &&e:edges)outdeg[e.from]++,indeg[e.to]++;
    }
    vector<int> deg_array(){
        calc_deg();
        return deg;
    }
    vector<int> indeg_array(){
        calc_deginout();
        return indeg;
    }
    vector<int> outdeg_array(){
        calc_deginout();
        return outdeg;
    }
    int get_deg(int u){
        calc_deg();
        return deg[u];
    }
    int get_indeg(int u){
        calc_deginout();
        return indeg[u];
    }
    int get_outdeg(int u){
        calc_deginout();
        return outdeg[u];
    }
};

template<class T,bool directed>
vector<T> dijkstra(const Graph<T,directed> &g,int source=0){
    using P = pair<T,int>;
    int n=g.n;
    vector<T> dist(n,T(-1));
    priority_queue<P,vector<P>,greater<P>> pq;
    dist[source]=0;
    pq.emplace(0,source);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(dist[u]<d)continue;
        for(auto &e:g.adj[u]){
            int v=e.to;
            T ndist=d+e.cost;
            if(dist[v]==T(-1)||ndist<dist[v]){
                dist[v]=ndist;
                pq.emplace(ndist,v);
            }
        }
    }
    return dist;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    Graph<ll,true> g(n);
    g.read(m,true);
    auto d=dijkstra(g);
    for(auto x:d)cout << x << " ";
}