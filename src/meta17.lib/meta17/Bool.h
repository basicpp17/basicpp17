#pragma once

namespace meta17 {

/// transport bools as types
template<bool B>
struct Bool {
    /// allow using instances in conditions
    constexpr explicit operator bool() const { return B; }
};

} // namespace meta17
