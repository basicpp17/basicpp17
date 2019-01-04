#pragma once
#include "SomeOf.h"

#include <meta17/Type.h>
#include <meta17/TypePack.h>

#include <meta17/Type.wrap.h> // UnwrapType

namespace some_of17 {

using meta17::Type;
using meta17::TypePack;
using meta17::UnwrapType;

template<class... Ts>
auto makeSomeOfType(TypePack<Ts...> = {}) -> Type<SomeOf<Ts...>> {
    return {};
}
template<class P>
using MakeSomeOf = UnwrapType<decltype(makeSomeOfType(P{}))>;

} // namespace some_of17
