#pragma once
#include "Tuple.h"

#include <meta17/TemplateOfTypes.trait.h>

namespace tuple17 {

using meta17::IsTypeTemplate;

template<class T>
using IsTuple = IsTypeTemplate<T, Tuple>;

template<class T>
constexpr auto is_tuple = IsTuple<T>{};

} // namespace tuple17
