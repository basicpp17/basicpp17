#pragma once
#include "Bool.h"

#include "DeferStaticError.h"
#include "same.h"

namespace meta17 {

/// Unwrapping
template<class T>
constexpr auto to_value = same<T, T>&& META17_DEFER_STATIC_ERROR("no value");

template<bool B>
constexpr auto to_value<Bool<B>> = B;

template<class T>
constexpr auto toValue(T) {
    return to_value<T>;
}

} // namespace meta17
