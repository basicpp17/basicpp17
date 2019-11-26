#pragma once
#include "IndexPack.for.h"
#include "Type.h"
#include "TypePack.indexOf.h"

#include "Type.ops.h" // type == type

namespace meta17 {

/// number of occurences of type T in the template of types
template<class T, class TT>
constexpr auto template_count_of = META17_STATIC_ERROR_EXPR(size_t, "not a type pack");

template<class T, template<typename...> class Template, class... Ts>
constexpr auto template_count_of<T, Template<Ts...>> = ((type<Ts> == type<T> ? 1 : 0) + ... + 0);

/// true only if T is in template of types
template<class T, class TT>
constexpr auto template_contains_of = META17_STATIC_ERROR_EXPR(bool, "not a type pack");

template<class T, template<typename...> class Template, class... Ts>
constexpr auto template_contains_of<T, Template<Ts...>> = ((type<Ts> == type<T>) || ...);

template<class T, template<typename...> class Template, class... Ts>
constexpr auto templateContainsOf(Type<Template<Ts...>>, Type<T> = {}) -> bool {
    return ((type<Ts> == type<T>) || ...);
}

/// index of the given T in the template
template<class T, class TT, class IP>
constexpr auto indexed_type_template_overflow_index_of = META17_STATIC_ERROR_EXPR(size_t, "not a type pack");

template<class T, template<typename...> class Template, class... Ts, size_t... Is>
constexpr auto indexed_type_template_overflow_index_of<T, Template<Ts...>, IndexPack<Is...>> = //
    1 == countOf<T, Ts...>() ? (((type<Ts> == type<T>) ? Is : 0) + ...) : sizeof...(Ts);

template<class T, class TT>
constexpr auto type_template_overflow_index_of = indexed_type_template_overflow_index_of<T, TT, IndexPackFor<TT>>;

/// statically asserts that the returned index is valid
template<class T, class TT, class IP>
constexpr auto indexed_type_template_index_of = META17_STATIC_ERROR_EXPR(size_t, "not a type pack");

template<class T, template<typename...> class Template, class... Ts, size_t... Is>
constexpr auto indexed_type_template_index_of<T, Template<Ts...>, IndexPack<Is...>> = //
    1 == countOf<T, Ts...>() ? (((type<Ts> == type<T>) ? Is : 0) + ...)
                             : META17_STATIC_ERROR_EXPR(size_t, "type not found");

template<class T, class TT>
constexpr auto type_template_index_of = indexed_type_template_index_of<T, TT, IndexPackFor<TT>>;

} // namespace meta17
