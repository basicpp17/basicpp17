#pragma once
#include "Const.h"
#include "ConstPack.h"

#include "Const.ops.h" // Const == Const
#include "IndexPack.for.h" // IndexPackFor

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
template<auto V, class CP>
constexpr auto contains_const = containsConst(CP{}, _const<V>);

/// return index of const V in ConstPack or size of ConstPack if V is not part or occurs multiple times
template<auto V, auto... Vs, size_t... Is>
constexpr auto indexConst(ConstPack<Vs...>, IndexPack<Is...>, Const<V> = {}) -> size_t {
    constexpr auto cp = const_pack<Vs...>;
    return 1 == countConst<V>(cp) ? (((_const<Vs> == _const<V>) ? Is : 0) + ...) : sizeof...(Vs);
}
template<auto V, class CP>
constexpr auto indexConst(CP = {}, Const<V> = {}) {
    using IP = IndexPackFor<CP>;
    return indexConst<V>(CP{}, IP{});
}
template<auto V, class CP>
constexpr auto index_const = indexConst<V, CP>();

} // namespace meta17
