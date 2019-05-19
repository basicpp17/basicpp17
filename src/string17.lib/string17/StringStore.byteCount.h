#pragma once
#include "StringStore.h"
#include "byteCount.h"

namespace string17 {

template<size_t N>
constexpr auto byteCount(AdlType<StringStore<N>>) -> size_t {
    return N;
}

} // namespace string17
