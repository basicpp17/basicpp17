#pragma once
#include "Const.h"

namespace meta17 {

template<class T>
constexpr auto is_const = false;

template<auto V>
constexpr auto is_const<Const<V>> = true;

} // namespace meta17
