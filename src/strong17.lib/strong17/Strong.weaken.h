#pragma once
#include "Strong.extract.h"
#include "Strong.h"
#include "Strong.trait.h"

#include <meta17/Type.h>
#include <meta17/TypePack.h>

#include <meta17/Type.wrap.h> // UnwrapType

#include <type_traits>

namespace strong17 {

using meta17::Type;
using meta17::type;
using meta17::TypePack;
using meta17::UnwrapType;

/// like extractValue, but does nothing for non-strong types
template<class S>
constexpr auto weakenType(Type<S> = {}) -> std::enable_if_t<is_strong<S>.v, Type<ExtractValue<Base<S>>>> {
    return {};
}
template<class T>
constexpr auto weakenType(Type<T> = {}) -> std::enable_if_t<!is_strong<T>.v, Type<T>> {
    return {};
}
template<class S>
using WeakenType = decltype(weakenType(type<S>));
template<class S>
constexpr auto weaken_type = WeakenType<S>{};
template<class S>
using WeakenTypeValue = UnwrapType<WeakenType<S>>;
template<class S>
constexpr auto weaken(S s) -> WeakenTypeValue<S> {
    if constexpr (is_strong<S>) {
        return s.v;
    }
    else {
        return s;
    }
}

} // namespace strong17
