#pragma once
#include "Value.h"

namespace meta17 {

template<auto v>
constexpr auto valueConstFn() -> decltype(auto) {
    return v;
}

// store simple constant as Value
template<auto v>
constexpr auto value_const = Value<&valueConstFn<v>>{};

} // namespace meta17
