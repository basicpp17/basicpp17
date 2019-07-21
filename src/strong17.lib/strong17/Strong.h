#pragma once
#include "meta17/DeferStaticError.h"

#include "Strong.trait.h"

namespace strong17 {

template<class T, class = void>
struct IsValidTag : std::true_type {};
template<class T>
struct IsValidTag<T, std::enable_if_t<std::is_enum_v<T>>> : std::true_type {};
template<class T>
struct IsValidTag<T, std::enable_if_t<!std::is_class_v<T>>> : std::false_type {};
template<class T>
struct IsValidTag<T, std::enable_if_t<std::is_class_v<T> && (sizeof(T) == sizeof(T))>> : std::is_empty<T> {};

template<class V, class... Tags>
constexpr auto checkStrongArgs() {
    if constexpr (is_strong<V>)
        return META17_DEFER_STATIC_ERROR("Nested Strong is not allowed!");
    else if constexpr (!std::is_object_v<V>)
        return META17_DEFER_STATIC_ERROR("Strong value should store something!");
    else if constexpr (sizeof...(Tags) < 1)
        return META17_DEFER_STATIC_ERROR("Strong requires at least one tag!");
    else if constexpr (!(IsValidTag<Tags>{} && ...))
        return META17_DEFER_STATIC_ERROR("All strong tags should not store anything!");
    else
        return meta17::DeferSuccess{};
}

/** \brief strong type alias
 *
 * features:
 * + no fuss (very simple)
 * + disallows nesting strong types (just add tags!)
 */
template<class V, class... Tags>
struct Strong {
    static_assert(checkStrongArgs<V, Tags...>()());
    V v{};

    constexpr Strong() = default;
    constexpr explicit Strong(V v)
        : v(v) {}
};

} // namespace strong17
