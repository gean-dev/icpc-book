#pragma once
#include "../template/Header.hpp"
#include "MontgomeryModInt.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-03-17
 * Description: basic combinatorics functions
 */

template<class mint=mint>
mint invmod(int x){
    static constexpr ll mod=mint::get_mod();
    static vector<mint> invs{0,1};
    for(int i=sz(invs);i<=x;i++)
        invs.push_back(mint(-mod/i*invs[mod%i]));
    return invs[x];
}

template<class mint=mint>
mint fac(int x){
    static vector<mint> facs{1};
    for(int i=sz(facs);i<=x;i++)
        facs.push_back(facs[i-1]*mint(i));
    return facs[x];
}

template<class mint=mint>
mint invfac(int x){
    static vector<mint> invs{1};
    for(int i=sz(invs);i<=x;i++)
        invs.push_back(invs[i-1]*invmod<mint>(i));
    return invs[x];
}

template<class mint=mint>
mint nPr(int n,int r){
    if(n<0||r<0||n<r)return mint(0);
    return fac<mint>(n)*invfac<mint>(n-r);
}

template<class mint=mint>
mint nCr(int n,int r){
    if(n<0||r<0||n<r)return mint(0);
    return fac<mint>(n)*invfac<mint>(n-r)*invfac<mint>(r);
}

