#pragma once

namespace meta17 {

/// transport bools as types
template<bool B>
struct Bool {
    constexpr static bool v = B;
    /// allow using instances in conditions
    constexpr operator bool() const { return B; }
};

/// instances
using True = Bool<true>;
using False = Bool<false>;

} // namespace meta17
