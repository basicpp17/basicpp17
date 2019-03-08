#pragma once
#include "Type.h"
#include "TypePack.h"

namespace meta17 {

/// invoke callable with all types of the TypePack
template<class Callable, class... Ts>
constexpr auto forEachType(TypePack<Ts...>, Callable&& callable) {
    return (..., callable(type<Ts>));
}

/// invoke callable with all types of the TypePack
template<template<class...> class Template, class... Ts>
constexpr auto wrapEachType(TypePack<Ts...>) {
    return TypePack<Template<Ts>...>{};
}

template<template<class...> class Template, class TP>
constexpr auto wrap_each_type = wrapEachType<Template>(TP{});

template<template<class...> class Template, class TP>
using WrapEachType = decltype(wrapEachType<Template>(TP{}));

/// return true if callable is true for every type of TypePack
template<class Callable, class... Ts>
constexpr bool allTypesOf(TypePack<Ts...>, Callable&& callable) {
    return (... && callable(type<Ts>));
}

} // namespace meta17
