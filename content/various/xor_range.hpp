#pragma once

/**
 * Author: Teetat T.
 * Date: 2024-11-27
 * Description: find all range of $x$ such that $l \le x$ xor $p < r$.
 */

template<class F>
void xor_range(ll p,ll l,ll r,const F &query){
    for(int i=0;i<60;i++){
        if(l==r)break;
        ll b=1LL<<i;
        if(l&b){
            query(l^p,(l^p)+b);
            l+=b;
        }
        if(r&b){
            r-=b;
            query(r^p,(r^p)+b);
        }
        if(p&b){
            p^=b;
        }
    }
}