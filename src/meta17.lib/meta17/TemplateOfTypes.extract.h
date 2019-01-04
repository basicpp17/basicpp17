#pragma once
#include "Type.h"
#include "TypePack.h"

#include "Type.wrap.h" // to_type

namespace meta17 {

/// Count template arguments
template<template<class...> class Template, class... Ts>
constexpr auto countTypes(Type<Template<Ts...>> = {}) -> size_t {
    return sizeof...(Ts);
}
template<class T>
constexpr auto count_types = countTypes(to_type<T>);

/// extract template arguments as TypePack
template<template<class...> class Template, class... Ts>
constexpr auto extractTypePack(Type<Template<Ts...>> = {}) -> TypePack<Ts...> {
    return {};
}
template<class T>
using ExtractTypePack = decltype(extractTypePack(to_type<T>));
template<class T>
constexpr auto extract_type_pack = ExtractTypePack<T>{};

/// extract first template argument
template<template<class...> class Template, class H, class... Ts>
constexpr auto extractHeadType(Type<Template<H, Ts...>> = {}) -> Type<H> {
    return {};
}
template<class T>
using ExtractHeadType = decltype(extractHeadType(to_type<T>));
template<class T>
constexpr auto extract_head_type = ExtractHeadType<T>{};

/// extract tailing template arguments
template<template<class...> class Template, class H, class... Ts>
constexpr auto extractTailTypePack(Type<Template<H, Ts...>> = {}) -> TypePack<Ts...> {
    return {};
}
template<class T>
using ExtractTailTypePack = decltype(extractTailTypePack(to_type<T>));
template<class T>
constexpr auto extract_tail_type_pack = ExtractTailTypePack<T>{};

} // namespace meta17
