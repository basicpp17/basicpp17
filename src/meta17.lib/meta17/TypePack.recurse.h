#pragma once
#include "TypePack.h"

#include "DeferStaticError.h"
#include "Type.h"
#include "Type.wrap.h"
#include "same.h"

namespace meta17 {

/// return count of types in a TypePack
template<class TP>
constexpr auto type_count = 0;
template<class... Ts>
constexpr auto type_count<TypePack<Ts...>> = sizeof...(Ts);

template<class TP>
constexpr auto typeCount(TP) {
    return type_count<TP>;
}

/// return first type in TypePack
/// note: only valid if typePack has at least one type (typeCount >= 1)
template<class H, class... Ts>
constexpr auto typeHead(TypePack<H, Ts...> = {}) -> H;

template<class TP>
using TypeHead = decltype(typeHead(TP{}));
template<class TP>
constexpr auto type_head = type<TypeHead<TP>>;

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
