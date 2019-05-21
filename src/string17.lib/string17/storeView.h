#pragma once
#include "StringStore.h"
#include "StringView.h"

namespace string17 {

template<size_t N>
constexpr auto storeView(const StringView& o) noexcept -> StringStore<N> {
    auto r = StringStore<N>{};
    auto i = 0U;
    for (; i < o.size(); i++) r.data[i] = o[i];
    for (; i < N; i++) r.data[i] = '\0';
    return r;
}

} // namespace string17
