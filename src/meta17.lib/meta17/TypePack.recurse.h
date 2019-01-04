#pragma once
#include "TypePack.h"

#include "Type.h"

namespace meta17 {

/// return count of types in a TypePack
template<class... Ts>
constexpr auto typeCount(TypePack<Ts...> = {}) {
    return sizeof...(Ts);
}
template<class TP>
constexpr auto type_count = typeCount(TP{});

/// return first type in TypePack
/// note: only valid if typePack has at least one type (typeCount >= 1)
template<class H, class... Ts>
constexpr auto typeHead(TypePack<H, Ts...> = {}) -> Type<H> {
    return {};
}
template<class TP>
using TypeHead = decltype(typeHead(TP{}));
template<class TP>
constexpr auto type_head = TypeHead<TP>{};

/// return TypePack excluding the first Type
/// note: only valid if typePack has at least one type (typeCount >= 1)
template<class H, class... Ts>
constexpr auto typeTail(TypePack<H, Ts...> = {}) -> TypePack<Ts...> {
    return {};
}
template<class TP>
using TypeTail = decltype(typeTail(TP{}));
template<class TP>
constexpr auto type_tail = TypeTail<TP>{};

} // namespace meta17
