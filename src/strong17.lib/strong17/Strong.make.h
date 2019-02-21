#pragma once
#include "Strong.h"

#include <meta17/Type.h>
#include <meta17/TypePack.h>

#include <meta17/Type.wrap.h> // UnwrapType

namespace strong17 {

using meta17::Type;
using meta17::type;
using meta17::TypePack;
using meta17::UnwrapType;

template<class Value, class... Tags>
constexpr auto makeStrongType(TypePack<Tags...> = {}, Type<Value> = {}) -> Type<Strong<Value, Tags...>> {
    return {};
}
template<class V, class TP>
using MakeStrongType = decltype(makeStrongType(TP{}, type<V>));

template<class V, class Tags>
constexpr auto make_strong_type = MakeStrongType<V, Tags>{};

template<class V, class Tags>
using MakeStrong = UnwrapType<MakeStrongType<V, Tags>>;

template<class Value, class... Tags>
constexpr auto makeOpaqueType(Type<Strong<Value, Tags...>>) -> Type<Strong<Value, Tags...>> {
    return {};
}
template<class S>
using MakeOpaqueType = decltype(makeOpaqueType(type<S>));

template<class S>
constexpr auto make_opaque_type = MakeOpaqueType<S>{};

template<class S>
using MakeOpaque = UnwrapType<MakeOpaqueType<S>>;

} // namespace strong17
