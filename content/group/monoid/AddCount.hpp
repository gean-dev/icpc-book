#pragma once
#include "../../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Add & Count Monoid class.
 */

template<class T>
struct AddCountMonoid{
    using P = pair<T,int>;
    using value_type = P;
    static constexpr P op(const P &x,const P &y){
        return P(x.first+y.first,x.second+y.second);
    }
    static constexpr P inverse(const P &x){return P(-x.first,-x.second);}
    static constexpr P unit(){return P(T(0),0);}
    static constexpr P make(const T &x){return P(x,1);}
};

