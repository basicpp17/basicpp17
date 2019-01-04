#pragma once
#include "OneOf.h"

#include <meta17/TemplateOfTypes.trait.h>

namespace one_of17 {

using meta17::IsTypeTemplate;

template<class T>
using IsOneOf = IsTypeTemplate<T, OneOf>;

template<class T>
constexpr auto is_one_of = IsOneOf<T>{};

} // namespace one_of17
