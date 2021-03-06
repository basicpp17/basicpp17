#pragma once
#include "StringStore.h"
#include "append.h"
#include "byteCount.h"

namespace string17 {

template<class... Ts>
constexpr auto concat(Ts... ts) {
    using namespace details;

    constexpr size_t N = (byteCount(adl, Ts{}) + ... + 0u);
    auto r = StringStore<N>{};
    auto p = static_cast<char*>(r.data);
    (append(p, ts, byteCount(adl, Ts{})), ...);
    return r;
}

} // namespace string17
