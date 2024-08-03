#pragma once
#include "../../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Max Monoid class.
 */

template<class T>
struct MaxMonoid{
    using value_type = T;
    static constexpr T op(const T &x,const T &y){return max(x,y);}
    static constexpr T unit(){return numeric_limits<T>::min();}
};

