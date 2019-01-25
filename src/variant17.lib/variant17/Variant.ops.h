#pragma once

#include "Variant.h"

namespace variant17 {

template<class... Ts>
bool constexpr operator==(const Variant<Ts...>& a, const Variant<Ts...>& b) {
    if (a.which() != b.which()) return false;

    return a.visit([&](auto x) {
        auto y = *b.asPtr(Type<decltype(x)>{});
        return x == y;
    });
}

template<class... Ts>
bool constexpr operator!=(const Variant<Ts...>& a, const Variant<Ts...>& b) {
    return !(a == b);
}

} // namespace variant17
