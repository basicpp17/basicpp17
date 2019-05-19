#pragma once
#include "StringView.h"

namespace string17 {

constexpr auto viewCString(const char* o) noexcept -> StringView {
    auto len = [](const char* p) {
        auto l = size_t{};
        while ('\0' != p[l]) l++;
        return l;
    }(o);
    return {&o[0], &o[len]}; // Skip '\0'
}

} // namespace string17
