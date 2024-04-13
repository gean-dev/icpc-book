#pragma once
#include "../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-01-15
 * Source: https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
 * Description: Extended Euclid algorithm for solving diophantine equation (ax + by = gcd(a, b)).
 * Time: $O(\log\max\{a,b\})$
 */

pair<ll,ll> euclid(ll a,ll b){
    ll x=1,y=0,x1=0,y1=1;
    while(b!=0){
        ll q=a/b;
        x-=q*x1;
        y-=q*y1;
        a-=q*b;
        swap(x,x1);
        swap(y,y1);
        swap(a,b);
    }
    return {x,y};
}

