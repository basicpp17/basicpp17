#pragma once
#include "StaticErrorExpr.h"
#include "Type.h"
#include "same.h"

#include <utility> // std::declval

namespace meta17 {

/// Count template type arguments
template<class T>
constexpr auto count_template_types = META17_STATIC_ERROR_EXPR(size_t, "no template of types");

template<template<class...> class Template, class... Ts>
constexpr auto count_template_types<Template<Ts...>> = sizeof...(Ts);

/// extract first template argument
template<template<class...> class Template, class H, class... Ts>
constexpr auto templateTypeHead(Template<H, Ts...>) -> H;

template<class TT>
using TemplateTypeHead = decltype(templateTypeHead(std::declval<TT>()));

template<class T>
constexpr auto template_type_head = type<TemplateTypeHead<T>>;

/// extract tailing template arguments
template<template<class...> class Template, class H, class... Ts>
constexpr auto templateTypeTail(Template<H, Ts...>) -> Template<Ts...>;

template<class TT>
using TemplateTypeTail = decltype(templateTypeTail(std::declval<TT>()));
template<class TT>
constexpr auto template_type_tail = TemplateTypeTail<TT>{};

} // namespace meta17
