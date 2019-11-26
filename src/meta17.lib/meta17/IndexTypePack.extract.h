#pragma once
#include "IndexTypePack.h"

#include "IndexPack.extract.h" // ExtractIndexPack
#include "StaticErrorExpr.h"
#include "same.h"

namespace meta17 {

// add oveload for TypePack of IndexType
template<size_t... Is, class... Ts>
constexpr auto extract_index_pack<TypePack<IndexType<Is, Ts>...>> = index_pack<Is...>;

/// extract TypePack from a TypePack of IndexType
template<class T>
constexpr auto extract_type_pack = META17_STATIC_ERROR_EXPR(T, "no type_pack to extract");

template<size_t... Is, class... Ts>
constexpr auto extract_type_pack<TypePack<IndexType<Is, Ts>...>> = type_pack<Ts...>;

template<class T>
using ExtractTypePack = decltype(extract_type_pack<T>);

} // namespace meta17
