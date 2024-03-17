#include <bits/stdc++.h>
#include "../../content/template/Header.hpp"
#include "../../content/polynomials/FFT.hpp"

using namespace std;

int rng(int x){
    return rand()%x;
}

int rng(int l,int r){
    assert(l<=r);
    return l+rng(r-l+1);
}

vl brute(const vl &a,const vl &b){
    int n=a.size(),m=b.size();
    vl res(n+m-1);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            res[i+j]+=a[i]*b[j];
            res[i+j]%=MOD;
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    const int N=100;
    const int T=100;
    auto test=[&](){
        int n=rng(1,N),m=rng(1,N);
        vl a(n),b(m);
        for(auto &x:a)x=rng(MOD);
        for(auto &x:b)x=rng(MOD);
        auto sol1=brute(a,b);
        auto sol2=FFT<ll,MOD>::convMod(a,b);
        assert(sol1==sol2);
    };
    for(int i=1;i<=T;i++)test();
    cout << "Tests passed!" << endl;
}