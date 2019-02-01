#pragma once
#include "Bool.h"

namespace meta17 {

/// transport a simple value as a type
template<auto>
struct Const {};

template<auto V>
constexpr auto _const = Const<V>{};

} // namespace meta17
