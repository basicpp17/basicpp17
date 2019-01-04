#pragma once
#include "Type.h"
#include "TypePack.h"

#include "Type.wrap.h" // to_type

namespace meta17 {

template<class T, template<class...> class Template, class... Ts>
constexpr auto addTypeToTemplate(Type<Template<Ts...>>, Type<T> = {}) -> Type<Template<Ts..., T>> {
    return {};
}

template<class Ns, template<class...> class Template, class... Ts>
constexpr auto addTypesToTemplate(Type<Template<Ts...>> = {}, TypePack<Ns...> = {}) -> Type<Template<Ts..., Ns...>> {
    return {};
}

// template<class T, template<class...> class Template, class... Ts>
// constexpr auto removeTypeFromTemplate(Type<Template<Ts...>>, Type<T> = {}) -> Type<Template<Ts..., T>> {
//    return {};
//}

} // namespace meta17
