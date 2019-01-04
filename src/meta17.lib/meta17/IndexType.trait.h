#pragma once
#include "IndexType.h"

#include "Bool.wrap.h"

#include <type_traits> // std::remove_const_t

namespace meta17 {

namespace trait {

template<class T>
struct IsIndexType : False {};

template<size_t I, class T>
struct IsIndexType<IndexType<I, T>> : True {};

} // namespace trait

template<class T>
using IsIndexType = trait::IsIndexType<std::remove_const_t<T>>;

template<class T>
constexpr auto is_index_type = IsIndexType<T>{};

} // namespace meta17
