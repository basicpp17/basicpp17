#pragma once
#include "TypePack.h"

#include "Type.wrap.h" // to_type

namespace meta17 {

/// extract template arguments as TypePack
template<template<class...> class Template, class... Ts>
constexpr auto extractTypePack(Type<Template<Ts...>> = {}) -> TypePack<Ts...> {
    return {};
}
template<class T>
using ExtractTypePack = decltype(extractTypePack(to_type<T>));
template<class T>
constexpr auto extract_type_pack = ExtractTypePack<T>{};

} // namespace meta17
