#pragma once

/**
 * Author: Teetat T.
 * Date: 2025-02-20
 * Description: Definite integral using Simpson's formula.
 */

template<class T,class F>
T difinite_integral(T a,T b,const F &f,int n){
    T res=0;
    T dx=(b-a)/n;
    T fl=0,fr=f(a);
    for(int i=0;i<n;i++){
        T l=a+dx*i;
        T r=l+dx;
        fl=fr;
        fr=f(r);
        T fm=f((l+r)/2);
        res+=fl+4*fm+fr;
    }
    return res*dx/6;
}