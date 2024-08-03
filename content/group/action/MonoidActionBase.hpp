#pragma once
#include "../../template/Header.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-05-16
 * Description: Monoid Action Base class.
 */

template<class MInfo,class MTag,typename MInfo::value_type
    (*combine)(typename MInfo::value_type,typename MTag::value_type)>
struct MonoidActionBase{
    using InfoMonoid = MInfo;
    using TagMonoid = MTag;
    using Info = typename InfoMonoid::value_type;
    using Tag = typename TagMonoid::value_type;
    static constexpr Info op(const Info &a,const Tag &b){
        return combine(a,b);
    }
};