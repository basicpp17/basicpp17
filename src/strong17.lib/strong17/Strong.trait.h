#pragma once

#include "Strong.h"

#include "meta17/TemplateOfTypes.trait.h"

namespace strong17 {

template<class T>
using IsStrong = meta17::IsTypeTemplate<T, Strong>;

template<class T>
constexpr auto is_strong = IsStrong<T>{};

} // namespace strong17
