#pragma once

#include <cstddef> // size_t

namespace string17 {

template<size_t N>
using StringArray = char[N];

template<size_t N>
struct StringStore {
    StringArray<N> data;

    static constexpr bool empty() noexcept { return N == 0; }
    static constexpr auto size() noexcept -> size_t { return N; }
    constexpr char operator[](size_t i) const noexcept { return data[i]; }
};

template<size_t N>
StringStore(const char (&)[N])->StringStore<N>;

} // namespace string17
