#pragma once
#include "Strong.h"

#include "meta17/TemplateOfTypes.trait.h"

namespace strong17 {

template<class T>
using IsStrong = meta17::IsTypeTemplate<T, Strong>;

} // namespace strong17
