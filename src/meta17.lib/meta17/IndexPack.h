#pragma once
#include "ConstPack.h"

namespace meta17 {

/// IndexPack is a specialized ConstPack
template<size_t... Is>
using IndexPack = ConstPack<Is...>;

template<size_t... Is>
constexpr auto index_pack = IndexPack<Is...>{};

} // namespace meta17
