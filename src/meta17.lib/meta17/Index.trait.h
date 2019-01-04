#pragma once
#include "Index.h"

#include "Bool.wrap.h"

#include <type_traits> // std::remove_const_t

// note: we cannot use TemplateOfValues.trait here!
// it seems template<size_t> differs from template<auto>

namespace meta17 {

namespace trait {

template<class T>
struct IsIndex : False {};

template<size_t I>
struct IsIndex<Index<I>> : True {};

} // namespace trait

template<class T>
using IsIndex = trait::IsIndex<std::remove_const_t<T>>;

template<class T>
constexpr auto is_index = IsIndex<T>{};

} // namespace meta17
