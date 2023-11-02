#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> p2;

template<class T=int,class CMP=greater<T>>
struct SparseTable{
    int n,lg;
    vector<vector<T>> t;
    CMP cmp;
    inline T max(T a,T b){return cmp(a,b)?a:b;}
    void init(int _n,vector<T> a){
        n=_n,lg=31-__builtin_clz(n);
        t.assign(lg+1,vector<T>(n+1));
        for(int i=1;i<=n;i++)t[0][i]=a[i];
        for(int i=1;i<=lg;i++){
            for(int j=1;j+(1<<i)-1<=n;j++){
                t[i][j]=max(t[i-1][j],t[i-1][j+(1<<(i-1))]);
            }
        }
    }
    T query (int l ,int r){
        int k=31-__builtin_clz(r-l+1);
        return max(t[k][l],t[k][r-(1<<k)+1]);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    
}