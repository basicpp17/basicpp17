#pragma once
#include "Const.h"

#include "TemplateOfValues.trait.h"

namespace meta17 {

template<class T>
using IsConst = IsValueTemplate<T, Const>;

template<class T>
constexpr auto is_const = IsConst<T>{};

} // namespace meta17
