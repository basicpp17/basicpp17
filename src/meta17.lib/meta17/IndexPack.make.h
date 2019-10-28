#pragma once
#include "IndexPack.h"

#include "Const.h"
#include "IndexPack.extract.h"

#include <utility> // std::make_index_sequence

namespace meta17 {

/// use std::make_index_sequence
template<size_t C>
constexpr auto make_index_pack = extract_index_pack<std::make_index_sequence<C>>;

template<size_t C>
using MakeIndexPack = decltype(make_index_pack<C>);

template<size_t C>
constexpr auto makeIndexPack(Const<C> = {}) {
    return make_index_pack<C>;
}

} // namespace meta17
