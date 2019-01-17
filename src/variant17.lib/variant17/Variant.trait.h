#pragma once
#include "Variant.h"

#include <meta17/TemplateOfTypes.trait.h>

namespace one_of17 {

using meta17::IsTypeTemplate;

template<class T>
using IsVariant = IsTypeTemplate<T, Variant>;

template<class T>
constexpr auto is_one_of = IsVariant<T>{};

} // namespace one_of17
