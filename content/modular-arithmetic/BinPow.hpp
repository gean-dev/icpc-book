#pragma once
#include "../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-01-15
 * Description: n-th power using divide and conquer
 * Time: $O(\log b)$
 */

template<class T>
constexpr T binpow(T a,ll b){
    T res=1;
    for(;b>0;b>>=1,a*=a)if(b&1)res*=a;
    return res;
}

