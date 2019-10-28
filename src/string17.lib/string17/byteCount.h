#pragma once
#include "meta17/Type.h"
#include "meta17/Value.h"

#include <type_traits>

namespace string17 {

using meta17::Value;

// ADL allows us to have all functions in scope
struct ADL {};
constexpr auto adl = ADL{};

constexpr auto byteCount(ADL, const char* p) -> size_t {
    auto l = size_t{};
    while ('\0' != p[l]) l++;
    return l;
}

template<class T>
constexpr auto byteCount(ADL, const T& t) -> decltype(t.size()) {
    return t.size();
}

constexpr auto byteCount(ADL, char) -> size_t { return 1; }

template<auto f>
constexpr auto byteCount(ADL, Value<f>) -> size_t {
    return byteCount(adl, Value<f>::v);
}

} // namespace string17
