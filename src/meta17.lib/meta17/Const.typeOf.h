#pragma once
#include "Const.h"
#include "Type.h"

namespace meta17 {

template<auto V>
constexpr auto typeOf(Const<V>) -> Type<decltype(V)> {
    return {};
}

template<class T>
using TypeOf = decltype(typeOf(T{}));

template<class T>
constexpr auto type_of = TypeOf<T>{};

} // namespace meta17
