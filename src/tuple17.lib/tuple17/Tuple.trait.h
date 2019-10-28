#pragma once
#include "Tuple.h"

namespace tuple17 {

template<class T>
constexpr auto is_tuple = false;

template<class... Ts>
constexpr auto is_tuple<Tuple<Ts...>> = true;

} // namespace tuple17
