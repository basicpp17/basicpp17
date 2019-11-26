#pragma once
#include "IndexPack.h"
#include "TypePack.h"

#include "IndexPack.for.h" // IndexPackFor
#include "Type.ops.h" // type == type

namespace meta17 {

/// return number of occurences of type T in the TypePack
template<class T, class... Ts>
constexpr auto count_of = ((type<Ts> == type<T> ? 1 : 0) + ... + 0);

template<class T, class... Ts>
constexpr auto count_of<T, TypePack<Ts...>> = count_of<T, Ts...>;

template<class T, class... Ts>
constexpr auto countOf(TypePack<Ts...> = {}, Type<T> = {}) -> size_t {
    return count_of<T, Ts...>;
}

/// return true if T occurs at least once in the TypePack
template<class T, class... Ts>
constexpr auto contains_of = ((type<Ts> == type<T>) || ...);

template<class T, class... Ts>
constexpr auto contains_of<T, TypePack<Ts...>> = contains_of<T, Ts...>;

template<class T, class... Ts>
constexpr auto containsOf(TypePack<Ts...>, Type<T> = {}) -> bool {
    return contains_of<T, Ts...>;
}

/// return index of type T in TypePack or size of TypePack if index is not part or occurs multiple times
template<class T, class TP, class IP>
constexpr auto indexed_type_pack_overflow_index_of = META17_STATIC_ERROR_EXPR(size_t, "not a type pack");

template<class T, class... Ts, size_t... Is>
constexpr auto indexed_type_pack_overflow_index_of<T, TypePack<Ts...>, IndexPack<Is...>> = //
    1 == countOf<T, Ts...>() ? (((type<Ts> == type<T>) ? Is : 0) + ...) : sizeof...(Ts);

template<class T, class TP, class IP>
constexpr auto indexedTypePackOverflowIndexOf(TP, IP) -> size_t {
    return indexed_type_pack_overflow_index_of<T, TP, IP>;
}

template<class T, class TP>
constexpr auto type_pack_overflow_index_of = indexed_type_pack_overflow_index_of<T, TP, IndexPackFor<TP>>;

template<class T, class TP>
constexpr auto typePackOverflowIndexOf(TP, Type<T> = {}) {
    return indexed_type_pack_overflow_index_of<T, TP, IndexPackFor<TP>>;
}

/// statically asserts that the returned index is valid
template<class T, class TP, class IP>
constexpr auto indexed_type_pack_index_of = META17_STATIC_ERROR_EXPR(size_t, "not a type pack");

template<class T, class... Ts, size_t... Is>
constexpr auto indexed_type_pack_index_of<T, TypePack<Ts...>, IndexPack<Is...>> = //
    1 == count_of<T, Ts...> ? (((type<Ts> == type<T>) ? Is : 0) + ...)
                            : META17_STATIC_ASSERT_EXPR(size_t, (1 == count_of<T, Ts...>), "type not found");

template<class T, class TP, class IP>
constexpr auto indexedTypePackIndexOf(TP = {}, IP = {}, Type<T> = {}) -> size_t {
    static_assert(0 < count_of<T, TP>, "type is not a member of TypePack");
    static_assert(2 > count_of<T, TP>, "type occurs multiple times in TypePack");
    return indexed_type_pack_index_of<T, TP, IP>;
}

template<class T, class TP>
constexpr auto type_pack_index_of = indexed_type_pack_index_of<T, TP, IndexPackFor<TP>>;

template<class T, class TP>
constexpr auto typePackIndexOf(TP = {}, Type<T> = {}) {
    return indexed_type_pack_index_of<T, TP, IndexPackFor<TP>>;
}

} // namespace meta17
