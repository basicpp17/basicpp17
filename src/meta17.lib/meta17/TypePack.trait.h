#pragma once
#include "TypePack.h"

#include "TemplateOfTypes.trait.h"

namespace meta17 {

template<class T>
using IsTypePack = IsTypeTemplate<T, TypePack>;

template<class T>
constexpr auto is_type_pack = IsTypePack<T>{};

} // namespace meta17
