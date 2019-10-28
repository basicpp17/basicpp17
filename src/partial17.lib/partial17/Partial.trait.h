#pragma once
#include "Partial.h"

namespace partial17 {

template<class T>
constexpr auto is_partial = false;

template<class... Ts>
constexpr auto is_partial<Partial<Ts...>> = true;

} // namespace partial17
