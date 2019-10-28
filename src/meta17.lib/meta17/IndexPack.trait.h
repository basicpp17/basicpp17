#pragma once
#include "IndexPack.h"

namespace meta17 {

template<class T>
constexpr auto is_index_pack = false;

template<size_t... Is>
constexpr auto is_index_pack<IndexPack<Is...>> = true;

} // namespace meta17
