#pragma once

#include "DeferStaticError.h"
#include "same.h"

#include <utility> // std::declval

namespace meta17 {

/// Count template value arguments
template<class T>
constexpr auto count_template_values = same<T, T>&& META17_DEFER_STATIC_ERROR("no template of values");

template<template<auto...> class Template, auto... Vs>
constexpr auto count_template_values<Template<Vs...>> = sizeof...(Vs);

/// extract first template value
template<class T>
constexpr auto head_template_values = same<T, T>&& META17_DEFER_STATIC_ERROR("no template of values");

template<template<auto...> class Template, auto V, auto... Vs>
constexpr auto head_template_values<Template<V, Vs...>> = V;

/// extract tailing template values
template<template<auto...> class Template, auto V, auto... Vs>
constexpr auto tailTemplateValues(Template<V, Vs...>) -> Template<Vs...>;
template<class T>
using TailTemplateValues = decltype(tailTemplateValues(std::declval<T>()));

} // namespace meta17
