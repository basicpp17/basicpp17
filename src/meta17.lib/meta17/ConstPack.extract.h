#pragma once
#include "ConstPack.h"

#include "DeferStaticError.h"
#include "same.h"

#include <type_traits>

namespace meta17 {

/// extract template value arguments as ConstPack
template<class T>
constexpr auto extract_const_pack = same<T, T>&& META17_DEFER_STATIC_ERROR("no template of values");

template<template<auto...> class Template, auto... Vs>
constexpr auto extract_const_pack<Template<Vs...>> = const_pack<Vs...>;

template<class T>
using ExtractConstPack = std::remove_const_t<decltype(extract_const_pack<T>)>;

} // namespace meta17
