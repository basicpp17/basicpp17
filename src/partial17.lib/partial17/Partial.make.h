#pragma once
#include "Partial.h"

#include <meta17/Type.h>
#include <meta17/TypePack.h>

#include <meta17/Type.wrap.h> // UnwrapType

namespace partial17 {

using meta17::Type;
using meta17::TypePack;
using meta17::UnwrapType;

template<class... Ts>
auto makePartialType(TypePack<Ts...> = {}) -> Type<Partial<Ts...>> {
    return {};
}
template<class P>
using MakePartial = UnwrapType<decltype(makePartialType(P{}))>;

} // namespace partial17
