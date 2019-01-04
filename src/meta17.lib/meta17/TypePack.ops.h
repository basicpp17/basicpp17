#pragma once
#include "TypePack.h"

#include "Type.h"
#include "Type.ops.h" // type == type

namespace meta17 {

/// Equality
template<class... As, class... Bs>
constexpr bool operator==(TypePack<As...>, TypePack<Bs...>) {
    if constexpr (sizeof...(As) != sizeof...(Bs))
        return false;
    else
        return ((type<As> == type<Bs>)&&...);
}
template<class... As, class... Bs>
constexpr bool operator!=(TypePack<As...> a, TypePack<Bs...> b) {
    return !(a == b);
}

/// Concatenations
template<class... As, class... Bs>
constexpr auto operator+(TypePack<As...>, TypePack<Bs...>) -> TypePack<As..., Bs...> {
    return {};
}
template<class... As, class B>
constexpr auto operator+(TypePack<As...>, Type<B>) -> TypePack<As..., B> {
    return {};
}
template<class A, class... Bs>
constexpr auto operator+(Type<A>, TypePack<Bs...>) -> TypePack<A, Bs...> {
    return {};
}

} // namespace meta17
