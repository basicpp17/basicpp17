#pragma once
#include <meta17/Type.h>
#include <meta17/Value.h>

#include <type_traits>

namespace string17 {

using meta17::Value;

// AdlType is in string17 and allows us to find all overloads here!
template<class T>
struct AdlType {};

constexpr auto byteCount(const char* p) -> size_t {
    auto l = size_t{};
    while ('\0' != p[l]) l++;
    return l;
}

template<class T>
constexpr auto byteCount(const T& t) -> decltype(t.size()) {
    return t.size();
}

constexpr auto byteCount(char) -> size_t { return 1; }
constexpr auto byteCount(AdlType<char>) -> size_t { return 1; }

template<auto f>
constexpr auto byteCount(AdlType<Value<f>>) -> size_t {
    return byteCount(Value<f>::v);
}

} // namespace string17
