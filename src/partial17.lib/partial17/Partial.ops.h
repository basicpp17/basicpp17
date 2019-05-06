#pragma once
#include "Partial.h"
#include <iostream>
namespace partial17 {

template<class... Ts>
bool constexpr operator==(const Partial<Ts...>& a, const Partial<Ts...>& b) {
    if (a.which() != b.which()) return false;

    bool equal = true;
    a.visitAll([&](auto i, auto) { equal &= (!a.which().at(i) || a.at(i) == b.at(i)); });
    return equal;
}

template<class... Ts>
bool constexpr operator!=(const Partial<Ts...>& a, const Partial<Ts...>& b) {
    return !(a == b);
}

} // namespace partial17
