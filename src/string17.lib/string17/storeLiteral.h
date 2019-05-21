#pragma once
#include "StringStore.h"

namespace string17 {

template<size_t N>
constexpr auto storeLiteral(const StringArray<N>& o) noexcept -> StringStore<N - 1> {
    auto r = StringStore<N - 1>{};
    for (auto i = 0U; i < N - 1; i++) r.data[i] = o[i];
    return r;
}

} // namespace string17
