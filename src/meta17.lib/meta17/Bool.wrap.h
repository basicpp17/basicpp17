#pragma once
#include "Bool.h"

#include "StaticErrorExpr.h"
#include "same.h"

namespace meta17 {

/// Unwrapping
template<class T>
constexpr auto to_value = META17_STATIC_ERROR_EXPR(T, "no value");

template<bool B>
constexpr auto to_value<Bool<B>> = B;

template<class T>
constexpr auto toValue(T) {
    return to_value<T>;
}

} // namespace meta17
