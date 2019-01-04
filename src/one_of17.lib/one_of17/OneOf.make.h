#pragma once
#include "OneOf.h"

#include <meta17/Type.h>
#include <meta17/TypePack.h>

#include <meta17/Type.wrap.h> // UnwrapType

namespace one_of17 {

using meta17::TypePack;
using meta17::UnwrapType;

template<class... Ts>
auto makeOneOfType(TypePack<Ts...> = {}) -> Type<OneOf<Ts...>> {
    return {};
}
template<class P>
using MakeOneOf = UnwrapType<decltype(makeOneOfType(P{}))>;

} // namespace one_of17
