#pragma once
#include "../../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Affine Transfomation Monoid class.
 */

template<class T>
struct AffineMonoid{
    using P = pair<T,T>;
    using value_type = P;
    static constexpr P op(const P &x,const P &y){
        return P(x.first*y.first,x.second*y.first+y.second);
    }
    static constexpr P unit(){return P(T(1),T(0));}
    static constexpr T eval(const P &f,const T &x){
        return f.first*x+f.second;
    }
};

