#pragma once
#include "TemplateOfValues.h"

#include "Bool.wrap.h"
#include "Type.h"

#include <type_traits> // std::remove_const_t

namespace meta17 {

namespace trait {

template<template<auto...> class, class>
struct IsValueTemplate : False {};

template<template<auto...> class Template, auto... Vs>
struct IsValueTemplate<Template, Template<Vs...>> : True {};

} // namespace trait

template<class T, template<auto...> class Template>
using IsValueTemplate = trait::IsValueTemplate<Template, std::remove_const_t<T>>;

} // namespace meta17
