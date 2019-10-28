#pragma once
#include "Index.h"
#include "IndexPack.h"
#include "TypePack.h"

#include "Arguments.fold.h" // AccumulateInstances
#include "Const.ops.h" // index - index
#include "ConstPack.recurse.h" // count
#include "IndexPack.for.h" // IndexPackFor
#include "TypePack.ops.h" // type_pack + type_pack
#include "TypePack.recurse.h" // typeHead, type_count & typeCount

#include <utility> // std::conditional_t, std::declval

namespace meta17 {

template<size_t I, class... Ts, size_t... Is>
constexpr auto indexedTypeAtPack(TypePack<Ts...>, IndexPack<Is...>) {
    constexpr auto p = accumulate_instances<std::conditional_t<(Is == I), TypePack<Ts>, TypePack<>>...>;
    static_assert(1 == typeCount(p), "wrong index");
    return p;
}
template<size_t I, class TP, class IP>
constexpr auto indexedTypeAt(TP, IP) -> decltype(typeHead(indexedTypeAtPack<I>(TP{}, IP{})));

template<size_t I, class TP, class IP>
using IndexedTypeAt = decltype(typeHead(indexedTypeAtPack<I>(TP{}, IP{})));
template<size_t I, class TP, class IP>
constexpr auto indexed_type_at = type<IndexedTypeAt<I, TP, IP>>;

/// the type at index I of the TypePack
template<size_t I, class TP>
using TypeAt = IndexedTypeAt<I, TP, IndexPackFor<TP>>;
template<size_t I, class TP>
constexpr auto type_at = type<TypeAt<I, TP>>;

template<class TP, class IP>
using IndexedTypeLast = IndexedTypeAt<type_count<TP> - 1, TP, IP>;

/// last type of the TypePack
template<class TP>
constexpr auto typeLast(TP = {}) -> IndexedTypeLast<TP, IndexPackFor<TP>>;
template<class TP>
using TypeLast = decltype(typeLast<TP>());
template<class TP>
constexpr auto type_last = type<TypeLast<TP>>;

} // namespace meta17
