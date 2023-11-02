#pragma GCC optimize("Ofast,unroll-loops,fast-math")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll=long long;
using ld=long double;
using pii=pair<int,int>;
using pll=pair<ll,ll>;

template<typename T, typename U = null_type>
using ordered_set=tree<T,U,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());
template<typename T> T randint(T l, T r){return uniform_int_distribution<T>(l,r)(rng);}
struct hasher{
	const ll C=ll(2e18*M_PI)+71;
	const int RANDOM=rng();
	size_t operator()(ll x)const{return __builtin_bswap64((x ^ RANDOM) * C);}
};
template<class T>
using chash=gp_hash_table<ll,T,hasher>;

void runcase(){
    
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}