#pragma once
#include "Partial.h"

#include <meta17/TemplateOfTypes.trait.h>

namespace partial17 {

using meta17::IsTypeTemplate;

template<class T>
using IsPartial = IsTypeTemplate<T, Partial>;

template<class T>
constexpr auto is_partial = IsPartial<T>{};

} // namespace partial17
