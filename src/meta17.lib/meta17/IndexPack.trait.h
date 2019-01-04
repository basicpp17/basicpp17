#pragma once
#include "IndexPack.h"

#include "Bool.wrap.h"

#include <type_traits> // std::remove_const_t

// note: we cannot use TemplateOfValues.trait here!
// it seems template<size_t> differs from template<auto>

namespace meta17 {

namespace trait {

template<class T>
struct IsIndexPack : False {};

template<size_t... Is>
struct IsIndexPack<IndexPack<Is...>> : True {};

} // namespace trait

template<class T>
using IsIndexPack = trait::IsIndexPack<std::remove_const_t<T>>;

template<class T>
constexpr auto is_index_pack = IsIndexPack<T>{};

} // namespace meta17
