#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
constexpr T binpow(T a,ll b){
    T res=1;
    for(;b>0;b>>=1,a*=a)if(b&1)res*=a;
    return res;
}

ll modmul(ll a,ll b,ll mod){
    ll res=(a*b-ll(1.l*a*b/mod)*mod)%mod;
    if(res<0)res+=mod;
    return res;
}

ll modinv(ll a,ll b){
    ll x=0,x1=1;
    while(a!=0){
        ll q=b/a;
        b-=q*a;
        x-=q*x1;
        swap(a,b);
        swap(x,x1);
    }
    return x;
}

template<ll M>
struct Mint{
    ll x;
    constexpr Mint():x(0){}
    constexpr Mint(ll x):x(norm(x%getMod())){}
    static ll Mod;
    constexpr static ll getMod(){return M>0?M:Mod;}
    constexpr static void setMod(ll Mod_){Mod=Mod_;}
    constexpr ll norm(ll x)const{if(x<0)x+=getMod();if(x>=getMod())x-=getMod();return x;}
    explicit constexpr operator ll()const{return x;}
    constexpr Mint operator-()const{Mint res;res.x=norm(-x);return res;}
    constexpr Mint inv()const{return modinv(x,getMod());}
    constexpr Mint &operator+=(const Mint &rhs){x=norm(x+rhs.x);return *this;}
    constexpr Mint &operator-=(const Mint &rhs){x=norm(x-rhs.x);return *this;}
    constexpr Mint &operator*=(const Mint &rhs){x=modmul(x,rhs.x,getMod());return *this;}
    constexpr Mint &operator/=(const Mint &rhs){x=modmul(x,rhs.inv().x,getMod());return *this;}
    constexpr Mint &operator++(){return *this+=1;}
    constexpr Mint &operator--(){return *this-=1;}
    constexpr Mint operator++(int){Mint res=*this;*this+=1;return res;}
    constexpr Mint operator--(int){Mint res=*this;*this-=1;return res;}
    friend constexpr Mint operator+(Mint lhs,const Mint &rhs){return lhs+=rhs;}
    friend constexpr Mint operator-(Mint lhs,const Mint &rhs){return lhs-=rhs;}
    friend constexpr Mint operator*(Mint lhs,const Mint &rhs){return lhs*=rhs;}
    friend constexpr Mint operator/(Mint lhs,const Mint &rhs){return lhs/=rhs;}
    friend istream &operator>>(istream &is,Mint &o){ll x{};is>>x;o=Mint(x);return is;}
    friend ostream &operator<<(ostream &os,const Mint &o){return os<<o.x;}
    friend constexpr bool operator==(const Mint &lhs,const Mint &rhs){return lhs.x==rhs.x;}
    friend constexpr bool operator!=(const Mint &lhs,const Mint &rhs){return lhs.x!=rhs.x;}
    friend constexpr bool operator<(const Mint &lhs,const Mint &rhs){return lhs.x<rhs.x;} // for std::map
};
template<>
ll Mint<0ll>::Mod=ll(1e18)+9;
using mint = Mint<MOD>;
using vm = vector<mint>;
mint invmod(int x){
    static vm invs{0,1};
    for(int i=sz(invs);i<=x;i++)
        invs.push_back(-MOD/i*invs[MOD%i]);
    return invs[x];
}

namespace fft{

using cd = complex<db>;
using vc = vector<cd> ;

void fft(vc &a){
  	int n=a.size(),L=31-__builtin_clz(n);
  	vc rt(n);
  	rt[1]=1;
  	for(int k=2;k<n;k*=2){
    	cd z=polar(db(1),PI/k);
    	for(int i=k;i<2*k;i++)rt[i]=i&1?rt[i/2]*z:rt[i/2];
  	}
	vi rev(n);
	for(int i=1;i<n;i++)rev[i]=(rev[i/2]|(i&1)<<L)/2;
	for(int i=1;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int k=1;k<n;k*=2)for(int i=0;i<n;i+=2*k)for(int j=0;j<k;j++){
		cd z=rt[j+k]*a[i+j+k];
		a[i+j+k]=a[i+j]-z;
		a[i+j]+=z;
	}
}

template<class T>
struct _conv{
	using vt = vector<T>;
	static const bool INT=true;
	template<class U>
	db norm(const U &x){
		return INT?round(x):x;
	}
	vt operator()(const vt &a,const vt &b){
		if(a.empty()||b.empty())return {};
		vt res(a.size()+b.size()-1);
		int L=32-__builtin_clz(res.size()),n=1<<L;
		vc in(n),out(n);
		copy(a.begin(),a.end(),in.begin());
		for(int i=0;i<b.size();i++)in[i].imag(b[i]);
		fft(in);
		for(auto &x:in)x*=x;
		for(int i=0;i<n;i++)out[i]=in[-i&(n-1)]-conj(in[i]);
		fft(out);
		for(int i=0;i<res.size();i++)res[i]=norm(imag(out[i])/(4*n));
		return res;
	}
};
template<>
struct _conv<db>{
	static const bool INT=false;
};
template<class T>
vector<T> conv(const vector<T> &a,const vector<T> &b){
	return _conv<T>()(a,b);
}

template<ll M=MOD>
struct _convMod{
	vl operator()(const vl &a,const vl &b){
		if(a.empty()||b.empty())return {};
		vl res(a.size()+b.size()-1);
		int L=32-__builtin_clz(res.size()),n=1<<L;
		ll cut=int(sqrt(M));
		vc in1(n),in2(n),out1(n),out2(n);
		for(int i=0;i<a.size();i++)in1[i]=cd(ll(a[i])/cut,ll(a[i])%cut); // a1 + i * a2
		for(int i=0;i<b.size();i++)in2[i]=cd(ll(b[i])/cut,ll(b[i])%cut); // b1 + i * b2
		fft(in1),fft(in2);
		for(int i=0;i<n;i++){
			int j=-i&(n-1);
			out1[j]=(in1[i]+conj(in1[j]))*in2[i]/(2.l*n); // f1 * (g1 + i * g2) = f1 * g1 + i f1 * g2
			out2[j]=(in1[i]-conj(in1[j]))*in2[i]/cd(0.l,2.l*n); // f2 * (g1 + i * g2) = f2 * g1 + i f2 * g2
		}
		fft(out1),fft(out2);
		for(int i=0;i<res.size();i++){
			ll x=round(real(out1[i])),y=round(imag(out1[i]))+round(real(out2[i])),z=round(imag(out2[i]));
			res[i]=((x%M*cut+y)%M*cut+z)%M; // a1 * b1 * cut^2 + (a1 * b2 + a2 * b1) * cut + a2 * b2
		}
		return res;
	}
};
template<int M=MOD>
vl conv(const vl &a,const vl &b){
	return _convMod<M>()(a,b);
}

} // namespace fft

namespace ntt{

const mint g=3;

void ntt(vm &a){
	int n=a.size(),L=31-__builtin_clz(n);
	vm rt(n);
	rt[1]=1;
	for(int k=2,s=2;k<n;k*=2,s++){
		mint z[]={1,binpow(g,MOD>>s)};
		for(int i=k;i<2*k;i++)rt[i]=rt[i/2]*z[i&1];
	}
	vi rev(n);
	for(int i=1;i<n;i++)rev[i]=(rev[i/2]|(i&1)<<L)/2;
	for(int i=1;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int k=1;k<n;k*=2)for(int i=0;i<n;i+=2*k)for(int j=0;j<k;j++){
		mint z=rt[j+k]*a[i+j+k];
		a[i+j+k]=a[i+j]-z;
		a[i+j]+=z;
	}
}

struct _conv{
	vm operator()(const vm &a,const vm &b){
		if(a.empty()||b.empty())return {};
		int s=a.size()+b.size()-1,n=1<<(32-__builtin_clz(s));
		mint inv=mint(n).inv();
		vm in1(a),in2(b),out(n);
		in1.resize(n),in2.resize(n);
		ntt(in1),ntt(in2);
		for(int i=0;i<n;i++)out[-i&(n-1)]=in1[i]*in2[i]*inv;
		ntt(out);
		return vm(out.begin(),out.begin()+s);
	}
};
vm conv(const vm &a,const vm &b){
	return _conv()(a,b);
}

} // namespace ntt

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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    FPS a(n);
    for(auto &x:a)cin >> x;
    FPS b=a.inv(n);
    for(auto x:b)cout << x << " ";
}