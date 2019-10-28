#pragma once
#include "TypePack.h"

namespace meta17 {

template<class T>
constexpr auto is_type_pack = false;

template<class... Ts>
constexpr auto is_type_pack<TypePack<Ts...>> = true;

} // namespace meta17
