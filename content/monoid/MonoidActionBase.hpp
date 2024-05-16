#pragma once
#include "../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-05-16
 * Description: Monoid Base class.
 */

template<typename InfoMonoid,typename TagMonoid,typename InfoMonoid::value_type
    (*combine)(typename InfoMonoid::value_type,typename TagMonoid::value_type)>
struct MonoidActionBase{
    using Info = typename InfoMonoid::value_type;
    using Tag = typename TagMonoid::value_type;
    static constexpr Info op(const Info &a,const Tag &b){
        return combine(a,b);
    }
};

