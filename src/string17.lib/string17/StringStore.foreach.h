#pragma once

#include "StringStore.h"

namespace string17 {

template<size_t N>
constexpr auto begin(const StringStore<N>& s) -> const char* {
    return &s.data[0];
}

template<size_t N>
constexpr auto end(const StringStore<N>& s) -> const char* {
    return begin(s) + s.size();
}

} // namespace string17
