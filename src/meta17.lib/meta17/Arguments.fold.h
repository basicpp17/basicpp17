#pragma once
#include "Type.h"
#include "TypePack.h"

#include <type_traits> // decay_t
// only basic operations that require no further headers!

namespace meta17 {

/// add all arguments
template<class A, class... T>
constexpr auto accumulateArguments(A a, T... t) -> decltype((a + ... + t)) {
    return (a + ... + t);
}

/// add all type instances
template<class A, class... T>
constexpr auto accumulateInstances = (A{} + ... + T{});

template<class A, class... T>
constexpr auto accumulateDeclVal() {
    return (std::declval<A>() + ... + std::declval<T>());
}

template<class... Ts>
using AccumulateInstances = decltype(accumulateDeclVal<Ts...>());

/// true if all arguments convert to true
/// note: allArguments() == true (no argument was false!)
template<class... Ts>
constexpr auto allArguments(Ts... a) -> bool {
    return (true && ... && a);
}

/// true if any argument converts to true
template<class... Ts>
constexpr auto anyArgument(Ts... a) -> bool {
    return (false || ... || a);
}

} // namespace meta17
