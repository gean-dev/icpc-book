#pragma once
#include "../../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Min Monoid class.
 */

template<class T>
struct MinMonoid{
    using value_type = T;
    static constexpr T op(const T &x,const T &y){return min(x,y);}
    static constexpr T unit(){return numeric_limits<T>::max();}
};