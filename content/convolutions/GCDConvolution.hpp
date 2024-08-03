#pragma once
#include "../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-07-29
 * Description: GCD Convolution.
 * Multiple Zeta Transform: $A^\prime[n]=\sum_{n|m}A[m]$.
 * Multiple Mobius Transform: $A[n]=\sum_{n|m}\mu(m/n)A^\prime[m]$.
 * Time: $O(N\log\log N)$.
 */

template<class T>
void multiple_zeta(vector<T> &a){
    int n=(int)a.size();
    vector<bool> is_prime(n,true);
    for(int p=2;p<n;p++){
        if(!is_prime[p])continue;
        for(int i=(n-1)/p;i>=1;i--){
            is_prime[i*p]=false;
            a[i]+=a[i*p];
        }
    }
}

template<class T>
void multiple_mobius(vector<T> &a){
    int n=(int)a.size();
    vector<bool> is_prime(n,true);
    for(int p=2;p<n;p++){
        if(!is_prime[p])continue;
        for(int i=1;i*p<n;i++){
            is_prime[i*p]=false;
            a[i]-=a[i*p];
        }
    }
}

template<class T>
vector<T> gcd_convolution(vector<T> a,vector<T> b){
    multiple_zeta(a);
    multiple_zeta(b);
    for(int i=0;i<(int)a.size();i++)a[i]*=b[i];
    multiple_mobius(a);
    return a;
}