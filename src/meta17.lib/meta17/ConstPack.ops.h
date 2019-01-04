#pragma once
#include "ConstPack.h"

#include "Const.h"

namespace meta17 {

/// Equality
template<auto... As, auto... Bs>
constexpr bool operator==(ConstPack<As...>, ConstPack<Bs...>) {
    if constexpr (sizeof...(As) != sizeof...(Bs))
        return false;
    else
        return ((As == Bs) && ...);
}
template<auto... As, auto... Bs>
constexpr bool operator!=(ConstPack<As...> a, ConstPack<Bs...> b) {
    return !(a == b);
}

/// Concatenations
template<auto... As, auto... Bs>
constexpr auto operator+(ConstPack<As...>, ConstPack<Bs...>) -> ConstPack<As..., Bs...> {
    return {};
}
template<auto... As, auto B>
constexpr auto operator+(ConstPack<As...>, Const<B>) -> ConstPack<As..., B> {
    return {};
}
template<auto A, auto... Bs>
constexpr auto operator+(Const<A>, ConstPack<Bs...>) -> ConstPack<A, Bs...> {
    return {};
}

} // namespace meta17
