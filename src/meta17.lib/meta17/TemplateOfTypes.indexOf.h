#pragma once
#include "IndexPack.for.h"
#include "Type.h"

#include "Type.ops.h" // type == type

namespace meta17 {

/// return number of occurences of type T in the TypePack
template<class T, template<typename...> class Template, class... Ts>
constexpr auto templateCountOf(Type<Template<Ts...>>, Type<T> = {}) -> size_t {
    return ((type<Ts> == type<T> ? 1 : 0) + ... + 0);
}
template<class T, class Template>
constexpr auto template_count_of = templateCountOf(type<Template>, type<T>);

template<class T, template<typename...> class Template, class... Ts>
constexpr auto templateContains(Type<Template<Ts...>>, Type<T> = {}) -> bool {
    return ((type<Ts> == type<T>) || ...);
}
template<class T, class Template>
constexpr auto template_contains = templateContains<T>(type<Template>);

template<class T, template<typename...> class Template, class... Ts, size_t... Is>
constexpr auto templateIndexOf(Type<Template<Ts...>>, IndexPack<Is...>, Type<T> = {}) -> size_t {
    using TP = TypePack<Ts...>;
    return 1 == templateCountOf<T>(type<TP>) ? (((type<Ts> == type<T>) ? Is : 0) + ...) : sizeof...(Ts);
}

template<class T, template<typename...> class Template, class... Ts>
constexpr auto templateIndexOf(Type<Template<Ts...>>, Type<T> = {}) {
    constexpr auto ip = indexPackFor<Ts...>();
    return templateIndexOf<T>(type<Template<Ts...>>, ip);
}

template<class T, class Template>
constexpr auto template_index_of = templateIndexOf(type<Template>, type<T>);

} // namespace meta17
