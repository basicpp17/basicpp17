#pragma once
#include "Const.h"
#include "ConstPack.h"

#include "Const.ops.h" // Const == Const

namespace meta17 {

/// return number of occurences of const V in the ConstPack
template<auto V, auto... Vs>
constexpr auto countConst(ConstPack<Vs...>, Const<V> = {}) -> size_t {
    return ((_const<Vs> == _const<V> ? 1 : 0) + ... + 0);
}
template<auto V, class CP>
constexpr auto count_const = countConst(CP{}, _const<V>);

/// return true if V occurs at least once in the ConstPack
template<auto V, auto... Vs>
constexpr auto containsConst(ConstPack<Vs...>, Const<V> = {}) -> bool {
    return ((_const<Vs> == _const<V>) || ...);
}
template<auto T, class CP>
constexpr auto contains_const = containsConst(CP{}, _const<T>);

} // namespace meta17
