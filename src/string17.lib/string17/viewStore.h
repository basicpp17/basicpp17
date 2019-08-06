#pragma once
#include "StringStore.h"
#include "StringView.h"

namespace string17 {

template<size_t N>
constexpr auto viewStore(const StringStore<N>& store) -> StringView {
    return {static_cast<const char*>(store.data), static_cast<const char*>(store.data) + N};
}

} // namespace string17
