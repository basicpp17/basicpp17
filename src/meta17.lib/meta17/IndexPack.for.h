#pragma once
#include "IndexPack.h"

#include "IndexPack.extract.h"
#include "TypePack.h"

#include <utility> // std::index_sequence_for

namespace meta17 {

/// use std::index_sequence_for
template<class... Ts>
constexpr auto indexPackFor(TypePack<Ts...> = {}) {
    return ExtractIndexPack<std::index_sequence_for<Ts...>>{};
}

template<auto... Vs>
constexpr auto indexPackFor(ConstPack<Vs...> = {}) {
    return ExtractIndexPack<std::make_index_sequence<sizeof...(Vs)>>{};
}

template<class P>
using IndexPackFor = decltype(indexPackFor(P{}));

} // namespace meta17
