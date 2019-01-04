#pragma once
#include "TypeList.h"

#include "IndexTypePack.make.h"

namespace meta17 {

template<class... Ts>
constexpr auto makeTypeList(TypePack<Ts...>) {
    return TypeList<MakeIndexTypePack<TypePack<Ts...>>>{};
}

template<class P>
using MakeTypeList = decltype(makeTypeList(P{}));

template<class P>
constexpr auto make_type_list = MakeTypeList<P>{};

} // namespace meta17
