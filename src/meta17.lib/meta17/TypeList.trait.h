#pragma once
#include "TypeList.h"

#include "TemplateOfTypes.trait.h"

namespace meta17 {

template<class T>
using IsTypeList = IsTypeTemplate<T, TypeList>;

template<class T>
constexpr auto is_type_list = IsTypeList<T>{};

} // namespace meta17
