#pragma once
#include "IndexPack.h"

#include "Const.h"
#include "IndexPack.extract.h"

// hand written generator would be too slow
#include <utility>

namespace meta17 {

/// use std::make_index_sequence
template<size_t C>
using MakeIndexPack = ExtractIndexPack<std::make_index_sequence<C>>;

template<size_t C>
constexpr auto make_index_pack = MakeIndexPack<C>{};

template<size_t C>
constexpr auto makeIndexPack(Const<C> = {}) -> MakeIndexPack<C> {
    return {};
}

} // namespace meta17
