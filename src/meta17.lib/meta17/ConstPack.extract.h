#pragma once
#include "ConstPack.h"

#include "StaticErrorExpr.h"
#include "same.h"

#include <type_traits>

namespace meta17 {

/// extract template value arguments as ConstPack
template<class T>
constexpr auto extract_const_pack = META17_STATIC_ERROR_EXPR(T, "no template of values");

template<template<auto...> class Template, auto... Vs>
constexpr auto extract_const_pack<Template<Vs...>> = const_pack<Vs...>;

template<class T>
using ExtractConstPack = std::remove_const_t<decltype(extract_const_pack<T>)>;

} // namespace meta17
