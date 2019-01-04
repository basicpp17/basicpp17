#pragma once
#include "Type.h"

namespace meta17 {

/// Comparison
template<class A, class B>
constexpr bool operator==(Type<A>, Type<B>) {
    return false;
}
template<class A>
constexpr bool operator==(Type<A>, Type<A>) {
    return true;
}
template<class A, class B>
constexpr bool operator!=(Type<A> a, Type<B> b) {
    return !(a == b);
}

} // namespace meta17
