#pragma once
#include "../../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Default Action class.
 */

template<class Monoid>
struct DefaultAction{
    using InfoMonoid = Monoid;
    using TagMonoid = Monoid;
    using Info = typename Monoid::value_type;
    using Tag = typename Monoid::value_type;
    static constexpr Info op(const Info &a,const Tag &b){
        return Monoid::op(a,b);
    }
};

