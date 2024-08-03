#pragma once
#include "../../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Add Monoid class.
 */

template<class T>
struct AddMonoid{
    using value_type = T;
    static constexpr T op(const T &x,const T &y){return x+y;}
    static constexpr T inverse(const T &x){return -x;}
    static constexpr T unit(){return T(0);}
};

