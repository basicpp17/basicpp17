#pragma once
#include "ConstPack.h"

#include "TemplateOfValues.trait.h"

namespace meta17 {

template<class T>
using IsConstPack = IsValueTemplate<T, ConstPack>;

template<class T>
constexpr auto is_const_pack = IsConstPack<T>{};

} // namespace meta17
