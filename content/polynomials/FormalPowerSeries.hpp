#pragma once
#include "../number-theory/ModularArithmetic.hpp"
#include "FFT.hpp"
#include "NTT.hpp"

template<class T,class MUL,ll M=0>
struct FormalPowerSeries:vector<T>{
    using vector<T>::vector;
    using FPS=FormalPowerSeries;

    FPS &operator+=(const FPS &rhs){
        if(rhs.size()>this->size())this->resize(rhs.size());
        for(int i=0;i<rhs.size();i++)(*this)[i]+=rhs[i];
        return *this;
    }
    FPS &operator+=(const T &rhs){
        if(this->empty())this->resize(1);
        (*this)[0]+=rhs;
        return *this;
    }
    FPS &operator-=(const FPS &rhs){
        if(rhs.size()>this->size())this->resize(rhs.size());
        for(int i=0;i<rhs.size();i++)(*this)[i]-=rhs[i];
        return *this;
    }
    FPS &operator-=(const T &rhs){
        if(this->empty())this->resize(1);
        (*this)[0]-=rhs;
        return *this;
    }
    FPS &operator*=(const FPS &rhs){
        auto res=MUL()(*this,rhs);
        return *this=FPS(res.begin(),res.end());
    }
    FPS &operator*=(const T &rhs){
        for(auto &a:*this)a*=rhs;
        return *this;
    }
    friend FPS operator+(FPS lhs,const FPS &rhs){return lhs+=rhs;}
    friend FPS operator+(FPS lhs,const T &rhs){return lhs+=rhs;}
    friend FPS operator+(const T &lhs,FPS &rhs){return rhs+=lhs;}
    friend FPS operator-(FPS lhs,const FPS &rhs){return lhs-=rhs;}
    friend FPS operator-(FPS lhs,const T &rhs){return lhs-=rhs;}
    friend FPS operator-(const T &lhs,FPS rhs){return -(rhs-lhs);}
    friend FPS operator*(FPS lhs,const FPS &rhs){return lhs*=rhs;}
    friend FPS operator*(FPS lhs,const T &rhs){return lhs*=rhs;}
    friend FPS operator*(const T &lhs,FPS rhs){return rhs*=lhs;}
    
    FPS operator-(){return (*this)*-1;}

    FPS rev(){
        FPS res(*this);
        reverse(res.beign(),res.end());
        return res;
    }
    FPS pre(int sz){
        FPS res(this->begin(),this->begin()+min((int)this->size(),sz));
        if(res.size()<sz)res.resize(sz);
        return res;
    }
    FPS operator>>(int sz){
        if(this->size()<=sz)return {};
        FPS res(*this);
        res.erase(res.begin(),res.begin()+sz);
        return res;
    }
    FPS operator<<(int sz){
        FPS res(*this);
        res.insert(res.begin(),sz,T{});
        return res;
    }
    FPS diff(){
        const int n=this->size();
        FPS res(max(0,n-1));
        for(int i=1;i<n;i++)res[i-1]=(*this)[i]*T(i);
        return res;
    }
    FPS integral(){
        const int n=this->size();
        FPS res(n+1);
        res[0]=0;
        if(n>0)res[1]=1;
        if(M){
            for(int i=2;i<=n;i++)res[i]=(-res[M%i])*(M/i);
        }else{
            for(int i=2;i<=n;i++)res[i]=T(1)/T(i);
        }
        for(int i=0;i<n;i++)res[i+1]*=(*this)[i];
        return res;
    }
    T eval(const T &x){
        T res=0,w=1;
        for(auto &a:*this)res+=a*w,w*=x;
        return res;
    }
    FPS inv(int deg=-1){
        assert(!this->empty()&&(*this)[0]!=T(0));
        if(deg==-1)deg=this->size();
        FPS res{T(1)/(*this)[0]};
        for(int i=2;i>>1<deg;i<<=1){
            res=(res*(T(2)-res*pre(i))).pre(i);
        }
        return res.pre(deg);
    }
    FPS log(int deg=-1){
        assert(!this->empty()&&(*this)[0]==T(1));
        if(deg==-1)deg=this->size();
        return (pre(deg).diff()*inv(deg)).pre(deg-1).integral();
    }
    FPS exp(int deg=-1){
        assert(this->empty()||(*this)[0]==T(0));
        if(deg==-1)deg=this->size();
        FPS res{T(1)};
        for(int i=2;i>>1<deg;i<<=1){
            res=(res*(pre(i)-res.log(i)+T(1))).pre(i);
        }
        return res.pre(deg);
    }
    FPS pow(ll k,int deg=-1){
        const int n=this->size();
        if(deg==-1)deg=n;
        if(k==0){
            FPS res(deg);
            if(deg)res[0]=T(1);
            return res;
        }
        for(int i=0;i<n;i++){
            if(__int128_t(i)*k>=deg)return FPS(deg,T(0));
            if((*this)[i]==T(0))continue;
            T rev=T(1)/(*this)[i];
            FPS res=(((*this*rev)>>i).log(deg)*k).exp(deg);
            res=((res*binpow((*this)[i],k))<<(i*k)).pre(deg);
            return res;
        }
        return FPS(deg,T(0));
    }
};
using FPS=FormalPowerSeries<mint,ntt::_conv,MOD>; // for mod with primitive root
template<ll M>
using MFPS=FormalPowerSeries<Mint<M>,fft::_convMod<M>,M>; // for arbitary mod
using DFPS=FormalPowerSeries<db,fft::_conv<db>>; // for double