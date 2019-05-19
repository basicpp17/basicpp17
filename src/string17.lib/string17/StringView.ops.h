#pragma once
#include "StringView.h"

namespace string17 {

constexpr bool operator==(StringView a, StringView b) noexcept {
    if (a.size() != b.size()) return false;
    for (auto i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

constexpr bool operator!=(StringView a, StringView b) noexcept { return !(a == b); }

} // namespace string17
