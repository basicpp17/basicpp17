#pragma once
#include "IndexTypePack.h"

namespace meta17 {

template<class T>
constexpr auto is_index_type_pack = false;

template<>
constexpr auto is_index_type_pack<TypePack<>> = true;

template<size_t... Is, class... Ts>
constexpr auto is_index_type_pack<TypePack<IndexType<Is, Ts>...>> = true;

} // namespace meta17
