#pragma once
#include "IndexType.h"

#include "Index.h"
#include "Type.h"

namespace meta17 {

/// Extract Index
template<size_t I, class T>
constexpr auto extractIndex(IndexType<I, T>) -> Index<I> {
    return {};
}
template<class T>
using ExtractIndex = decltype(extractIndex(T{}));
template<class T>
constexpr auto extract_index = ExtractIndex<T>{};

/// Extract Type
template<size_t I, class T>
constexpr auto extractType(IndexType<I, T>) -> T;

template<class T>
using ExtractType = decltype(extractType(T{}));
template<class T>
constexpr auto extract_type = type<ExtractType<T>>;

} // namespace meta17
