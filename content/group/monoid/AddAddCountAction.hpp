#pragma once
#include "../../template/Header.hpp"
#include "Add.hpp"
#include "AddCount.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Add to Add & Count Monoid class.
 */

template<class T>
struct AddAddCountAction{
    using InfoMonoid = AddCountMonoid<T>;
    using TagMonoid = AddMonoid<T>;
    using Info = typename InfoMonoid::value_type;
    using Tag = typename TagMonoid::value_type;
    static constexpr Info op(const Info &a,const Tag &b){
        return Info(a.first+a.second*b,a.second);
    }
};

