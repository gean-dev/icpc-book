/**
 * Author: Teetat Thamronglak
 * Date: 2024-01-15
 * Description: modular arithmetic operations
 */
#pragma once
#include "../template/Header.hpp"

ll modmul(ll a,ll b,ll mod){
    ll res=(a*b-ll(1.l*a*b/mod)*mod)%mod;
    if(res<0)res+=mod;
    return res;
}

ll modinv(ll a,ll b){
    ll x=1,x1=0;
    while(a!=0){
        ll q=b/a;
        a-=q*b;
        x-=q*x1;
        swap(a,b);
        swap(x,x1);
    }
    return x;
}

struct mint{
    ll x;
    constexpr mint(ll x=0):x(norm(x%MOD)){}
    constexpr ll norm(ll x)const{if(x<0)x+=MOD;if(x>=MOD)x-=MOD;return x;}
    explicit constexpr operator ll()const{return x;}
    constexpr mint operator-()const{return mint(-x);}
    constexpr mint inv()const{return modinv(x,MOD);}
    constexpr mint &operator+=(const mint &rhs){x=norm(x+rhs.x);return *this;}
    constexpr mint &operator-=(const mint &rhs){x=norm(x-rhs.x);return *this;}
    constexpr mint &operator*=(const mint &rhs){x=modmul(x,rhs.x,MOD);return *this;}
    constexpr mint &operator/=(const mint &rhs){x=modmul(x,rhs.inv().x,MOD);return *this;}
    constexpr mint &operator++(){return *this+=1;}
    constexpr mint &operator--(){return *this-=1;}
    constexpr mint operator++(int){mint res=*this;*this+=1;return res;}
    constexpr mint operator--(int){mint res=*this;*this-=1;return res;}
    friend constexpr mint operator+(mint lhs,const mint &rhs){return lhs+=rhs;}
    friend constexpr mint operator-(mint lhs,const mint &rhs){return lhs-=rhs;}
    friend constexpr mint operator*(mint lhs,const mint &rhs){return lhs*=rhs;}
    friend constexpr mint operator/(mint lhs,const mint &rhs){return lhs/=rhs;}
    friend istream &operator>>(istream &is,mint &o){ll x{};is>>x;o=mint(x);return is;}
    friend ostream &operator<<(ostream &os,const mint &o){return os<<o.x;}
    friend constexpr bool operator==(const mint &lhs,const mint &rhs){return lhs.x==rhs.x;};
    friend constexpr bool operator!=(const mint &lhs,const mint &rhs){return lhs.x!=rhs.x;};
    friend constexpr bool operator<(const mint &lhs,const mint &rhs){return lhs.x!=rhs.x;}; // for std::map
};
using vm = vector<mint>;
mint invmod(int x){
    static vm invs{0,1};
    for(int i=sz(invs);i<=x;i++)
        invs.push_back(-MOD/i*invs[MOD%i]);
    return invs[x];
}