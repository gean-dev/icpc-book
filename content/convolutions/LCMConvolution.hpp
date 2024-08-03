#pragma once
#include "../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-07-29
 * Description: LCM Convolution.
 * Divisor Zeta Transform: $A^\prime[n]=\sum_{d|n}A[d]$.
 * Divisor Mobius Transform: $A[n]=\sum_{d|n}\mu(n/d)A^\prime[d]$.
 * Time: $O(N\log\log N)$.
 */

template<class T>
void divisor_zeta(vector<T> &a){
    int n=(int)a.size();
    vector<bool> is_prime(n,true);
    for(int p=2;p<n;p++){
        if(!is_prime[p])continue;
        for(int i=1;i*p<n;i++){
            is_prime[i*p]=false;
            a[i*p]+=a[i];
        }
    }
}

template<class T>
void divisor_mobius(vector<T> &a){
    int n=(int)a.size();
    vector<bool> is_prime(n,true);
    for(int p=2;p<n;p++){
        if(!is_prime[p])continue;
        for(int i=(n-1)/p;i>=1;i--){
            is_prime[i*p]=false;
            a[i*p]-=a[i];
        }
    }
}

template<class T>
vector<T> lcm_convolution(vector<T> a,vector<T> b){
    divisor_zeta(a);
    divisor_zeta(b);
    for(int i=0;i<(int)a.size();i++)a[i]*=b[i];
    divisor_mobius(a);
    return a;
}