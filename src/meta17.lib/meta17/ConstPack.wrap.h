#pragma once
#include "ConstPack.h"

#include "Bool.wrap.h" // to_value
#include "Const.wrap.h"

namespace meta17 {

/// Allow singe value extraction
template<auto V>
constexpr auto to_value<ConstPack<V>> = V;

/// Wrapping
template<class... Ts>
using ToConstPack = ConstPack<to_value<Ts>...>;

template<class... Ts>
constexpr auto to_const_pack = ToConstPack<Ts...>{};

} // namespace meta17
