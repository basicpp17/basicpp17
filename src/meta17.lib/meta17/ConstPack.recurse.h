#pragma once
#include "Const.h"
#include "ConstPack.h"

namespace meta17 {

/// return number of values in ConstPack
template<auto... Vs>
constexpr auto constCount(ConstPack<Vs...> = {}) -> size_t {
    return sizeof...(Vs);
}
template<class CP>
constexpr auto const_count = constCount(CP{});

/// return first value in ConstPack
/// note: only valid if ConstPack has at least one value (constCount >= 1)
template<auto H, auto... Vs>
constexpr auto constHead(ConstPack<H, Vs...> = {}) -> Const<H> {
    return {};
}
template<class CP>
using ConstHead = decltype(constHead(CP{}));
template<class CP>
constexpr auto const_head = ConstHead<CP>{};

/// return ConstPack excluding the first value
/// note: only valid if ConstPack has at least one value (constCount >= 1)
template<auto H, auto... Vs>
constexpr auto constTail(ConstPack<H, Vs...> = {}) -> ConstPack<Vs...> {
    return {};
}
template<class CP>
using ConstTail = decltype(constTail(CP{}));
template<class CP>
constexpr auto const_tail = ConstTail<CP>{};

} // namespace meta17
