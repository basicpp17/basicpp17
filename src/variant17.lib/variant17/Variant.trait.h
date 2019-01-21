#pragma once
#include "Variant.h"

#include <meta17/TemplateOfTypes.trait.h>

namespace variant17 {

using meta17::IsTypeTemplate;

template<class T>
using IsVariant = IsTypeTemplate<T, Variant>;

template<class T>
constexpr auto is_variant = IsVariant<T>{};

} // namespace variant17
