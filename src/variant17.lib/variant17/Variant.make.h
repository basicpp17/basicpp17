#pragma once
#include "Variant.h"

#include <meta17/Type.h>
#include <meta17/TypePack.h>

#include <meta17/Type.wrap.h> // UnwrapType

namespace variant17 {

using meta17::TypePack;
using meta17::UnwrapType;

template<class... Ts>
auto makeVariantType(TypePack<Ts...> = {}) -> Type<Variant<Ts...>> {
    return {};
}
template<class P>
using MakeVariant = UnwrapType<decltype(makeVariantType(P{}))>;

} // namespace variant17
