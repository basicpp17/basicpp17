#pragma once
#include "Variant.h"

namespace variant17 {

template<class T>
constexpr auto is_variant = false;

template<class... Ts>
constexpr auto is_variant<Variant<Ts...>> = true;

} // namespace variant17
