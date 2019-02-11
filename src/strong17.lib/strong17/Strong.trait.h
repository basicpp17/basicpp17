#pragma once

#include "Strong.base.h"
#include "Strong.h"

#include "meta17/TemplateOfTypes.trait.h"

namespace strong17 {

template<class, class = void>
struct IsStrong : ::meta17::False {};

template<class T>
struct IsStrong<T, std::void_t<Base<T>>> : meta17::IsTypeTemplate<Base<T>, Strong> {};

template<class T>
constexpr auto is_strong = IsStrong<std::remove_cv_t<T>>{};

} // namespace strong17
