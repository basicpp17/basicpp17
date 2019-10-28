#pragma once
#include "IndexPack.h"
#include "TypePack.h"

#include "DeferStaticError.h"
#include "same.h"

namespace meta17 {

/// sizeof every type in typepack
template<class TP>
constexpr auto sizeof_pack = same<TP, TP>&& META17_DEFER_STATIC_ERROR("no typepack given");

template<class... Ts>
constexpr auto sizeof_pack<TypePack<Ts...>> = const_pack<sizeof(Ts)...>;

template<class TP>
using SizeofPack = std::remove_const_t<decltype(sizeof_pack<TP>)>;

template<class... Ts>
constexpr auto sizeofPack(TypePack<Ts...> = {}) -> ConstPack<sizeof(Ts)...> {
    return {};
}

/// alignof every type in typepack
template<class TP>
constexpr auto alignof_pack = same<TP, TP>&& META17_DEFER_STATIC_ERROR("no typepack given");

template<class... Ts>
constexpr auto alignof_pack<TypePack<Ts...>> = const_pack<alignof(Ts)...>;

template<class TP>
using AlignofPack = std::remove_const_t<decltype(alignof_pack<TP>)>;

template<class... Ts>
constexpr auto alignofPack(TypePack<Ts...> = {}) -> ConstPack<alignof(Ts)...> {
    return {};
}

} // namespace meta17
