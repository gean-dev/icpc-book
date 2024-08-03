#pragma once
#include "../../template/Header.hpp"
#include "Add.hpp"
#include "Max.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-04-14
 * Description: Add to Max Action class.
 */

template<class T>
struct AddMaxAction{
    using InfoMonoid = MaxMonoid<T>;
    using TagMonoid = AddMonoid<T>;
    using Info = typename InfoMonoid::value_type;
    using Tag = typename TagMonoid::value_type;
    static constexpr Info op(const Info &a,const Tag &b){
        return (a==InfoMonoid::unit()?a:(a+b));
    }
};

