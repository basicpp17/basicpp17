#pragma once
#include "StringView.h"

namespace string17 {

template<size_t N>
using StringArray = char[N];

template<size_t N>
constexpr auto viewLiteral(const StringArray<N>& o) noexcept -> StringView {
    return {&o[0], &o[N - 1]}; // Skip '\0'
}

} // namespace string17
