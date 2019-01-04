#pragma once
#include "Type.h"

#include "TemplateOfTypes.wrap.h"

namespace meta17 {

template<class T>
using UnwrapType = UnwrapTemplate<T, TemplateOfTypes<Type>>;

template<class T>
using ToType = ToTemplate<TemplateOfTypes<Type>, T>;

template<class T>
constexpr auto to_type = ToType<T>{};

} // namespace meta17
