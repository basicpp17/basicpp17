#pragma once
#include "Strong.base.h"

#include "meta17/Bool.h"
#include "meta17/TemplateOfTypes.trait.h"
#include "meta17/same.h"

namespace strong17 {

using meta17::Bool;
using meta17::False;
using meta17::is_type_template;
using meta17::same;

template<class T, class = void>
constexpr auto is_strong = false;

template<class T>
constexpr auto is_strong<T, std::void_t<Base<T>>> = is_type_template<Base<T>, Strong>;

template<class, class = void>
struct IsOpaque : False {};

template<class T>
struct IsOpaque<T, std::enable_if_t<!same<T, Base<T>>>> : meta17::True {};

template<class T>
constexpr auto is_opaque = IsOpaque<std::remove_const_t<T>>{};

} // namespace strong17

#include "Strong.h"
