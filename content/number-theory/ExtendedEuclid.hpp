/**
 * Author: Teetat Thamronglak
 * Date: 2024-01-15
 * Source: cp-algorithms
 * Description: extended euclid algorithm;
 * Time: $O(\log\max\{a,b\})$
 */
#pragma once
#include "../template/Header.hpp"

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