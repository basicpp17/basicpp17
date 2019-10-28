#pragma once
#include "Const.h"
#include "ConstPack.h"

#include "DeferStaticError.h"
#include "same.h"

#include <cstddef> // size_t

namespace meta17 {

/// return number of values in ConstPack
template<class CP>
constexpr auto const_count = same<CP, CP>&& META17_DEFER_STATIC_ERROR("nothing to count");

template<auto... Vs>
constexpr auto const_count<ConstPack<Vs...>> = sizeof...(Vs);

/// return first value in ConstPack
/// note: only valid if ConstPack has at least one value (constCount >= 1)
template<class CP>
constexpr auto const_head = same<CP, CP>&& META17_DEFER_STATIC_ERROR("wrong type");

template<auto H, auto... Vs>
constexpr auto const_head<ConstPack<H, Vs...>> = H;

template<auto H, auto... Vs>
constexpr auto constHead(ConstPack<H, Vs...> = {}) {
    return H;
}

/// return ConstPack excluding the first value
/// note: only valid if ConstPack has at least one value (constCount >= 1)
template<class CP>
constexpr auto const_tail = same<CP, CP>&& META17_DEFER_STATIC_ERROR("wrong type");

template<auto H, auto... Vs>
constexpr auto const_tail<ConstPack<H, Vs...>> = const_pack<Vs...>;

template<class CP>
using ConstTail = std::remove_const_t<decltype(const_tail<CP>)>;

template<auto H, auto... Vs>
constexpr auto constTail(ConstPack<H, Vs...> = {}) -> ConstPack<Vs...> {
    return {};
}

} // namespace meta17
