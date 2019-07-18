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

template<typename V, class... Tags>
void take_strong(Strong<V, Tags...>&&);

template<typename T, typename = decltype(take_strong(T{}))>
using enable_if_strong = T;

template<class O>
struct Strong<enable_if_strong<O>> {
    static_assert(std::is_same_v<O, void>, "Do not nest Strong types!");
};

} // namespace strong17
