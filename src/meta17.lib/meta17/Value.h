#pragma once

namespace meta17 {

/// transport any compile time constant in a type
/// \param f has to be callable
template<auto f>
struct Value {
    static constexpr auto v{f()};
};

template<auto f>
constexpr auto value = Value<f>{};

} // namespace meta17
