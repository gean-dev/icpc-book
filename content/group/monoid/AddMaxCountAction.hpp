#pragma once
#include "../../template/Header.hpp"
#include "Add.hpp"
#include "MaxCount.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Add to Max & Count Action class.
 */

template<class T>
struct AddMaxCountAction{
    using InfoMonoid = MaxCountMonoid<T>;
    using TagMonoid = AddMonoid<T>;
    using Info = typename InfoMonoid::value_type;
    using Tag = typename TagMonoid::value_type;
    static constexpr Info op(const Info &a,const Tag &b){
        if(a.first==InfoMonoid::unit().first)return a;
        return Info(a.first+b,a.second);
    }
};

