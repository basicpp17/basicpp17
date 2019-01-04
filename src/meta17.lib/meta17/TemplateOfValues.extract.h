#pragma once
#include "Const.h"
#include "ConstPack.h"
#include "Type.h"

#include "Type.wrap.h" // to_type

namespace meta17 {

/// Count template value arguments
template<template<auto...> class Template, auto... Vs>
constexpr auto countValues(Type<Template<Vs...>> = {}) -> size_t {
    return sizeof...(Vs);
}
template<class T>
constexpr auto count_values = countTypes(to_type<T>);

/// extract template value arguments as ConstPack
template<template<auto...> class Template, auto... Vs>
constexpr auto extractConstPack(Type<Template<Vs...>> = {}) -> ConstPack<Vs...> {
    return {};
}
template<class T>
using ExtractConstPack = decltype(extractConstPack(to_type<T>));
template<class T>
constexpr auto extract_const_pack = ExtractConstPack<T>{};

/// extract first template value as Const
template<template<auto...> class Template, auto H, auto... Vs>
constexpr auto extractHeadConst(Type<Template<H, Vs...>> = {}) -> Const<H> {
    return {};
}
template<class T>
using ExtractHeadConst = decltype(extractHeadConst(to_type<T>));
template<class T>
constexpr auto extract_head_const = ExtractHeadConst<T>{};

/// extract tailing template values as ConstPack
template<template<auto...> class Template, auto H, auto... Vs>
constexpr auto extractTailConstPack(Type<Template<H, Vs...>> = {}) -> ConstPack<Vs...> {
    return {};
}
template<class T>
using ExtractTailConstPack = decltype(extractTailConstPack(to_type<T>));
template<class T>
constexpr auto extract_tail_const_pack = ExtractTailConstPack<T>{};

} // namespace meta17
