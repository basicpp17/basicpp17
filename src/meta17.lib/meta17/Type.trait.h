#pragma once
#include "Type.h"

#include "TemplateOfTypes.trait.h"

namespace meta17 {

template<class T>
using IsType = IsTypeTemplate<T, Type>;

template<class T>
constexpr auto is_type = IsType<T>{};

} // namespace meta17
