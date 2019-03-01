#pragma once
#include "Partial.h"
#include <iostream>
namespace partial17 {

template<class... Ts>
bool constexpr operator==(const Partial<Ts...>& a, const Partial<Ts...>& b) {
    if (a.bitset() != b.bitset()) return false;

    bool equal = true;
    a.visitAll([&](auto i, auto) { equal &= (a.has(i) == b.has(i)) && (!a.has(i) || a.get(i) == b.get(i)); });
    return equal;
}

template<class... Ts>
bool constexpr operator!=(const Partial<Ts...>& a, const Partial<Ts...>& b) {
    return !(a == b);
}

} // namespace partial17
