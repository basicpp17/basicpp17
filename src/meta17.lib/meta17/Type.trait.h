#pragma once
#include "Type.h"

namespace meta17 {

template<class T>
constexpr auto is_type = false;

template<class T>
constexpr auto is_type<Type<T>> = true;

} // namespace meta17
