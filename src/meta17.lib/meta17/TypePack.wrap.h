#pragma once
#include "TypePack.h"

#include "TemplateOfTypes.wrap.h"
#include "Type.wrap.h"

namespace meta17 {

template<class T>
using UnwrapTypePack = UnwrapTemplate<T, TemplateOfTypes<TypePack>>;

template<class... Ts>
using ToTypePack = ToTemplate<TemplateOfTypes<TypePack>, UnwrapType<Ts>...>;

template<class... Ts>
constexpr auto to_type_pack = ToTypePack<Ts...>{};

} // namespace meta17
