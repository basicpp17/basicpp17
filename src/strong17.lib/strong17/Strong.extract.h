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

/// return the value type for a given strong type
template<class V, class... Tags>
auto extractValueType(Type<Strong<V, Tags...>> = {}) -> Type<V> {
    return {};
}
template<class S>
using ExtractValueType = decltype(extractValueType(type<S>));
template<class S>
constexpr auto extract_value_type = ExtractValueType<S>{};
template<class S>
using ExtractValue = UnwrapType<ExtractValueType<S>>;

/// return the type pack of tags for a given strong type
template<class V, class... Tags>
auto extractTagsPack(Type<Strong<V, Tags...>> = {}) -> TypePack<Tags...> {
    return {};
}
template<class S>
using ExtractTagsPack = decltype(extractTagsPack(type<S>));
template<class S>
constexpr auto extract_tags_pack = ExtractTagsPack<S>{};

} // namespace strong17
