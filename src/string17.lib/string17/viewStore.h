#pragma once
#include "StringStore.h"
#include "StringView.h"

namespace string17 {

template<size_t N>
constexpr auto viewStore(const StringStore<N>& store) -> StringView {
    auto ptr = static_cast<const char*>(store.data);
    return {ptr, ptr + N};
}

} // namespace string17
