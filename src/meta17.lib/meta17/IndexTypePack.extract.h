#pragma once
#include "IndexTypePack.h"

#include "IndexPack.extract.h" // ExtractIndexPack

namespace meta17 {

namespace details {

// add oveload for TypePack of IndexType
template<size_t... Is, class... Ts>
struct ExtractIndexPack<TypePack<IndexType<Is, Ts>...>> {
    using Return = IndexPack<Is...>;
};

} // namespace details

/// extract TypePack from a TypePack of IndexType
template<size_t... Is, class... Ts>
constexpr auto extractTypePack(TypePack<IndexType<Is, Ts>...>) -> TypePack<Ts...> {
    return {};
}
template<class T>
using ExtractTypePack = decltype(extractTypePack(T{}));
template<class T>
constexpr auto extract_type_pack = ExtractTypePack<T>{};

} // namespace meta17
