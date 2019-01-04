#pragma once
#include "TypeList.h"

#include "TypePack.ops.h"

namespace meta17 {

template<class A, class B>
constexpr bool operator==(TypeList<A>, TypeList<B>) {
    return A{} == B{};
}

template<class A, class B>
constexpr bool operator!=(TypeList<A>, TypeList<B>) {
    return !(TypeList<A>{} == TypeList<B>{});
}

} // namespace meta17
