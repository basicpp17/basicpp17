#pragma once
#include "Value.h"

namespace meta17 {

template<auto& r>
constexpr auto valueRefFn() -> decltype(auto) {
    return r;
}

// complex static constexpr objects as reference (note: value stores a copy)
template<auto& r>
constexpr auto value_ref = Value<&valueRefFn<static_cast<decltype(r)>(r)>>{};

} // namespace meta17
