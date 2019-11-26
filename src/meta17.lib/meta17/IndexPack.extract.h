#pragma once
#include "IndexPack.h"

#include "StaticErrorExpr.h"
#include "same.h"

namespace meta17 {

/// allow std::integer_sequence like constructs to be converted
template<class T>
constexpr auto extract_index_pack = META17_STATIC_ERROR_EXPR(T, "no index_pack to extract");

template<template<size_t...> class Template, size_t... Is>
constexpr auto extract_index_pack<Template<Is...>> = index_pack<Is...>;

template<template<class, size_t...> class Template, size_t... Is>
constexpr auto extract_index_pack<Template<size_t, Is...>> = index_pack<Is...>;

template<class T>
using ExtractIndexPack = decltype(extract_index_pack<T>);

} // namespace meta17
