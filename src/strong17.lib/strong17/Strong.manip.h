#pragma once
#include "Strong.h"

#include "Strong.make.h" // MakeStrongType

#include <meta17/Type.h>

#include <meta17/Type.wrap.h> // UnwrapType
#include <meta17/TypePack.indexOf.h> // containsOf
#include <meta17/TypePack.manip.h> // RemoveType, ReplaceType

namespace strong17 {

using meta17::Type;
using meta17::type;
using meta17::TypePack;
using meta17::UnwrapType;

/// add one additional tag to strong type
template<class Add, class V, class... Tags>
constexpr auto addStrongTag(Type<Strong<V, Tags...>>, Type<Add> = {}) {
    static_assert(!(std::is_same_v<Tags, Add> || ...), "Added Tag is already present!");
    return Type<Strong<V, Tags..., Add>>{};
}
template<class T, class S>
using AddStrongTag = UnwrapType<decltype(addStrongTag<T>(type<S>))>;

/// add multiple tags to strong type
template<class... Adds, class V, class... Tags>
constexpr auto addStrongTags(Type<Strong<V, Tags...>>, TypePack<Adds...> = {}) {
    using AddPack = TypePack<Adds...>;
    static_assert(!(meta17::contains_of<Tags, AddPack> || ...), "One of the added Tags is already present!");
    return Type<Strong<V, Tags..., Adds...>>{};
}
template<class TP, class S>
using AddStrongTags = UnwrapType<decltype(addStrongTags(type<S>, TP{}))>;

/// remove one tag
template<class Remove, class V, class... Tags>
constexpr auto removeStrongTag(Type<Strong<V, Tags...>>, Type<Remove> = {}) {
    static_assert((std::is_same_v<Tags, Remove> || ...), "Removed Tag is not present!");
    return MakeStrongType<V, meta17::RemoveType<Remove, TypePack<Tags...>>>{};
}
template<class T, class S>
using RemoveStrongTag = UnwrapType<decltype(removeStrongTag<T>(type<S>))>;

/// replace one tag
template<class From, class To, class V, class... Tags>
constexpr auto replaceStrongTag(Type<Strong<V, Tags...>>, Type<From> = {}, Type<To> = {}) {
    static_assert((std::is_same_v<Tags, From> || ...), "Replaced Tag is not present!");
    static_assert(!(std::is_same_v<Tags, To> || ...), "To Tag is already present!");
    return MakeStrongType<V, meta17::ReplaceType<From, To, TypePack<Tags...>>>{};
}
template<class F, class T, class S>
using ReplaceStrongTag = UnwrapType<decltype(replaceStrongTag<F, T>(type<S>))>;

/// change strong value type
template<class To, class From, class... Tags>
constexpr auto changeStrongValue(Type<Strong<From, Tags...>>, Type<To> = {}) -> Type<Strong<To, Tags...>> {
    return {};
}
template<class T, class S>
using ChangeStrongValue = UnwrapType<decltype(changeStrongValue<T>(type<S>))>;

} // namespace strong17
