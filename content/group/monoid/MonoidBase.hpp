#pragma once

/**
 * Author: Teetat T.
 * Date: 2024-05-16
 * Description: Monoid Base class.
 */

template<class T,T (*combine)(T,T),T (*identity)()>
struct MonoidBase{
    using value_type = T;
    static constexpr T op(const T &x,const T &y){return combine(x,y);}
    static constexpr T unit(){return identity();}
};