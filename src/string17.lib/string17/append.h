#pragma once
#include "meta17/Value.h"

#include <type_traits>

namespace string17 {
namespace details {

using meta17::Value;

constexpr auto append(char*& o, const char* p, size_t n) {
    for (auto i = 0u; i < n; i++) *o++ = *p++;
}

template<class T>
constexpr auto append(char*& o, T& p, size_t n)
    -> std::enable_if_t<std::is_same_v<decltype(p[p.size() - 1]), decltype(p[0])>> {
    for (auto i = 0u; i < p.size(); ++i) *o++ = p[i];
}

constexpr auto append(char*& o, char p, size_t) { *o++ = p; }

template<auto f>
constexpr auto append(char*& o, Value<f>, size_t n) {
    return append(o, Value<f>::v, n);
}

} // namespace details
} // namespace string17
