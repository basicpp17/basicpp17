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

#include <utility> // std::conditional_t

namespace meta17 {

template<size_t I, class... Ts, size_t... Is>
constexpr auto indexedTypeAt(TypePack<Ts...>, IndexPack<Is...>, Index<I> = {}) {
    constexpr auto p = accumulateInstances<std::conditional_t<(Is == I), TypePack<Ts>, TypePack<>>...>;
    static_assert(1 == typeCount(p), "wrong index");
    return typeHead(p);
}

/// returns the type at index I of the TypePack
template<size_t I, class TP>
constexpr auto typeAt(TP = {}, Index<I> = {}) {
    using IP = IndexPackFor<TP>;
    return indexedTypeAt<I>(TP{}, IP{});
}
template<class I, class TP>
using TypeAt = decltype(typeAt(TP{}, I{}));
template<class I, class TP>
constexpr auto type_at = typeAt(TP{}, I{});

template<class TP, class IP>
constexpr auto indexedTypeLast(TP = {}, IP = {}) {
    constexpr auto lastIndex = index<type_count<TP>> - index<1>;
    return indexedTypeAt(TP{}, IP{}, lastIndex);
}

/// returns the last type of the TypePack
template<class TP>
constexpr auto typeLast(TP = {}) {
    using IP = IndexPackFor<TP>;
    return indexedTypeLast<TP, IP>();
}
template<class TP>
using TypeLast = decltype(typeLast<TP>());
template<class TP>
constexpr auto type_last = typeLast<TP>();

} // namespace meta17
