#pragma once
#include "IndexType.h"

#include "Type.ops.h" // type == type

namespace meta17 {

/// Equality
template<size_t AI, class AT, size_t BI, class BT>
constexpr bool operator==(IndexType<AI, AT>, IndexType<BI, BT>) {
    return (AI == BI) && (type<AT> == type<BT>);
}
template<size_t AI, class AT, size_t BI, class BT>
constexpr bool operator!=(IndexType<AI, AT> a, IndexType<BI, BT> b) {
    return !(a == b);
}

} // namespace meta17
