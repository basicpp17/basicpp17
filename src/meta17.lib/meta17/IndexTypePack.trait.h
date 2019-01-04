#pragma once
#include "IndexTypePack.h"

#include "Arguments.fold.h" // allArguments
#include "IndexType.trait.h" // is_index_type

namespace meta17 {

namespace trait {

template<class T>
struct IsIndexTypePack : False {};

template<class... Ts>
struct IsIndexTypePack<TypePack<Ts...>> : Bool<allArguments(is_index_type<Ts>...)> {};

} // namespace trait

template<class T>
using IsIndexTypePack = trait::IsIndexTypePack<std::remove_const_t<T>>;

template<class T>
constexpr auto is_index_type_pack = IsIndexTypePack<T>{};

} // namespace meta17
