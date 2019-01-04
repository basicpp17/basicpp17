#pragma once
#include "IndexPack.h"

#include "Bool.wrap.h" // to_value
#include "ConstPack.wrap.h"

namespace meta17 {

/// Unwrapping
// to_value works just fine

/// Wrapping
template<class... Ts>
using ToIndexPack = IndexPack<to_value<Ts>...>;

template<class... Ts>
constexpr auto to_index_pack = ToIndexPack<Ts...>{};

} // namespace meta17
