#pragma once
#include "ConstPack.h"

namespace meta17 {

template<class T>
constexpr auto is_const_pack = false;

template<auto... Vs>
constexpr auto is_const_pack<ConstPack<Vs...>> = true;

} // namespace meta17
