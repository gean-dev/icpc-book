#pragma once

/**
 * Author: Teetat T.
 * Date: 2024-09-21
 * Description: Floor sum function.
 *  $f(a, b, c, n) = \sum_{x=0}^n \lfloor \frac{ax+b}{c} \rfloor$
 *  becareful when a,b,c are negetive (use custom floor division and mod instead)
 * Time: $O(\log a)$
 */

ll floor_sum(ll a,ll b,ll c,ll n){
    ll res=n*(n+1)/2*(a/c)+(n+1)*(b/c);
    a%=c,b%=c;
    if(a==0)return res;
    ll m=(a*n+b)/c;
    return res+n*m-floor_sum(c,c-b-1,a,m-1);
}