#pragma once
#include "../../template/Header.hpp"
#include "AddCount.hpp"
#include "Affine.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Affine to Add & Count Action class.
 */

template<class T>
struct AffineAddCountAction{
    using InfoMonoid = AddCountMonoid<T>;
    using TagMonoid = AffineMonoid<T>;
    using Info = typename InfoMonoid::value_type;
    using Tag = typename TagMonoid::value_type;
    static constexpr Info op(const Info &a,const Tag &b){
        return Info(a.first*b.first+a.second*b.second,a.second);
    }
};

