#pragma once
#include "IndexType.h"

#include "same.h"

namespace meta17 {

/// Equality
template<size_t AI, class AT, size_t BI, class BT>
constexpr bool operator==(IndexType<AI, AT>, IndexType<BI, BT>) {
    return same<IndexType<AI, AT>, IndexType<BI, BT>>;
}
template<size_t AI, class AT, size_t BI, class BT>
constexpr bool operator!=(IndexType<AI, AT> a, IndexType<BI, BT> b) {
    return !(a == b);
}

} // namespace meta17
