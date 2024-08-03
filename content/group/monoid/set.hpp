#pragma once
#include "../../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-15
 * Description: Set Monoid class.
 */

template<class T>
struct SetMonoid{
    using P = pair<T,bool>;
    using value_type = P;
    static constexpr P op(const P &x,const P &y){return y.second?y:x;}
    static constexpr P unit(){return P(T(),false);}
    static constexpr P make(const T &x){return P(x,true);}
};

