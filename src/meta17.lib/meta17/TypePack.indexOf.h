#pragma once
#include "IndexPack.h"
#include "TypePack.h"

#include "IndexPack.for.h" // IndexPackFor
#include "Type.ops.h" // type == type

namespace meta17 {

/// return number of occurences of type T in the TypePack
template<class T, class... Ts>
constexpr auto countOf(TypePack<Ts...>, Type<T> = {}) -> size_t {
    return ((type<Ts> == type<T> ? 1 : 0) + ... + 0);
}
template<class T, class TP>
constexpr auto count_of = countOf(TP{}, type<T>);

/// return true if T occurs at least once in the TypePack
/*
template<class T, class... Ts>
constexpr auto containsOf(TypePack<Ts...>, Type<T> = {}) -> bool {
    return ((type<Ts> == type<T>) || ...);
}*/

// Generic Version
template<class T, class... Ts, template<typename...> class C>
constexpr auto containsOf(C<Ts...>, Type<T> = {}) -> bool {
    return ((type<Ts> == type<T>) || ...);
}
template<class T, class TP>
constexpr auto contains_of = containsOf(TP{}, type<T>);

/// return index of type T in TypePack or size of TypePack if index is not part or occurs multiple times
template<class T, class... Ts, size_t... Is>
constexpr auto indexOf(TypePack<Ts...>, IndexPack<Is...>, Type<T> = {}) -> size_t {
    constexpr auto tp = TypePack<Ts...>{};
    return 1 == countOf<T>(tp) ? (((type<Ts> == type<T>) ? Is : 0) + ...) : sizeof...(Ts);
}

template<class T, class TP>
constexpr auto indexOf(TP = {}, Type<T> = {}) {
    using IP = IndexPackFor<TP>;
    return indexOf<T>(TP{}, IP{});
}

/// statically asserts that the returned index is valid
template<class T, class TP, class IP>
constexpr auto checkedIndexOf(TP = {}, IP = {}, Type<T> = {}) -> size_t {
    static_assert(0 < countOf<T>(TP{}), "type is not a member of TypePack");
    static_assert(2 > countOf<T>(TP{}), "type occurs multiple times in TypePack");
    return indexOf<T>(TP{}, IP{});
}

template<class T, class TP>
constexpr auto checkedIndexOf(TP = {}, Type<T> = {}) {
    using IP = IndexPackFor<TP>;
    return checkedIndexOf<T>(TP{}, IP{});
}

} // namespace meta17
