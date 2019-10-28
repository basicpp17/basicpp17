#pragma once
#include "TypePack.h"

#include "Type.h"
#include "same.h"

namespace meta17 {

/// Equality
template<class... As, class... Bs>
constexpr bool operator==(TypePack<As...>, TypePack<Bs...>) {
    return same<TypePack<As...>, TypePack<Bs...>>;
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
