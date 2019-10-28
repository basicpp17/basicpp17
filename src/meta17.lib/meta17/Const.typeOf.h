#pragma once
#include "Const.h"
#include "Type.h"

namespace meta17 {

template<auto V>
constexpr auto constTypeOf(Const<V>) -> decltype(V);

template<class T>
using ConstTypeOf = decltype(constTypeOf(T{}));

template<class T>
constexpr auto const_type_of = type<ConstTypeOf<T>>;

} // namespace meta17
