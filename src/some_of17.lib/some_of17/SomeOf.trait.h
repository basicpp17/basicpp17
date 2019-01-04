#pragma once
#include "SomeOf.h"

#include <meta17/TemplateOfTypes.trait.h>

namespace some_of17 {

using meta17::IsTypeTemplate;

template<class T>
using IsSomeOf = IsTypeTemplate<T, SomeOf>;

template<class T>
constexpr auto is_some_of = IsSomeOf<T>{};

} // namespace some_of17
