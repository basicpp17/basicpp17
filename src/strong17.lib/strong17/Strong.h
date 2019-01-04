#pragma once
#include <utility> // std::is_same_v

namespace strong17 {

/** \brief strong type alias
 *
 * features:
 * + no fuss (very simple)
 * + disallows nesting strong types (just add tags!)
 */
template<class V, class...>
struct Strong {
    V v{};

    constexpr Strong() = default;
    constexpr explicit Strong(V v)
        : v(v) {}
};

template<class V, class... InnerTags, class... Tags>
struct Strong<Strong<V, InnerTags...>, Tags...> {
    static_assert(std::is_same_v<Strong<V, InnerTags...>, void>, "Do not nest Strong types!");
};

} // namespace strong17
