#pragma once
#include "IndexPack.h"

namespace meta17 {

namespace details {

template<class>
struct ExtractIndexPack;

template<template<size_t...> class Template, size_t... Is>
struct ExtractIndexPack<Template<Is...>> {
    using Return = IndexPack<Is...>;
};
template<template<class, size_t...> class Template, size_t... Is>
struct ExtractIndexPack<Template<size_t, Is...>> {
    using Return = IndexPack<Is...>;
};

} // namespace details

/// allow std::integer_sequence like constructs to be converted
template<class T>
using ExtractIndexPack = typename details::ExtractIndexPack<T>::Return;
template<class T>
constexpr auto extract_index_pack = ExtractIndexPack<T>{};

} // namespace meta17
