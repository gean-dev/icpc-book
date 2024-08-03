#pragma once
#include "../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-07-29
 * Description: Bitwise AND Convolution.
 * Superset Zeta Transform: $A^\prime[S]=\sum_{T\supseteq S}A[T]$.
 * Superset Mobius Transform: $A[T]=\sum_{S\supseteq T}(-1)^{|S-T|}A^\prime[S]$.
 * Time: $O(N\log N)$.
 */

template<class T>
void superset_zeta(vector<T> &a){
    int n=(int)a.size();
    assert(n==(n&-n));
    for(int i=1;i<n;i<<=1){
        for(int j=0;j<n;j++){
            if(j&i){
                a[j^i]+=a[j];
            }
        }
    }
}

template<class T>
void superset_mobius(vector<T> &a){
    int n=(int)a.size();
    assert(n==(n&-n));
    for(int i=n;i>>=1;){
        for(int j=0;j<n;j++){
            if(j&i){
                a[j^i]-=a[j];
            }
        }
    }
}

template<class T>
vector<T> and_convolution(vector<T> a,vector<T> b){
    superset_zeta(a);
    superset_zeta(b);
    for(int i=0;i<(int)a.size();i++)a[i]*=b[i];
    superset_mobius(a);
    return a;
}