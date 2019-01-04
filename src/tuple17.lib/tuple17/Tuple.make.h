#pragma once
#include "Tuple.h"

#include <meta17/Type.h>
#include <meta17/TypePack.h>

#include <meta17/Type.wrap.h> // UnwrapType

namespace tuple17 {

using meta17::TypePack;
using meta17::UnwrapType;

template<class... Ts>
auto makeTupleType(TypePack<Ts...> = {}) -> Type<Tuple<Ts...>> {
    return {};
}
template<class P>
using MakeTuple = UnwrapType<decltype(makeTupleType(P{}))>;

} // namespace tuple17
