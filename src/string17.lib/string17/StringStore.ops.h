#pragma once
#include "StringStore.h"

namespace string17 {

template<size_t N, size_t M>
constexpr bool operator==(const StringStore<N>&, const StringStore<M>&) {
    return false;
}

template<size_t N>
constexpr bool operator==(const StringStore<N>& a, const StringStore<N>& b) {
    for (int i = 0; i < N; ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

template<size_t N, size_t M>
constexpr bool operator!=(const StringStore<N>& a, const StringStore<M>& b) {
    return !(a == b);
}

} // namespace string17
