#pragma once
#include "Variant.h"

namespace variant17 {

template<class T>
constexpr auto is_variant = false;

template<class... Ts>
constexpr auto is_variant<Variant<Ts...>> = true;

template<class T>
constexpr auto is_variant_which = false;

template<class... Ts>
constexpr auto is_variant_which<VariantWhich<Ts...>> = true;

} // namespace variant17
