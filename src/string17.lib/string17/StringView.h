#pragma once

namespace string17 {

struct StringView {
    const char* begin{};
    const char* end{};

    constexpr bool empty() const noexcept { return begin >= end; }
    constexpr auto size() const noexcept -> size_t { return static_cast<size_t>(end - begin); }
    constexpr char operator[](size_t i) const noexcept { return begin[i]; }
};

} // namespace string17
