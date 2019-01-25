#pragma once

#include "TemplateOfTypes.h"

#include "Bool.wrap.h"
#include "Type.h"

#include <type_traits> // std::remove_const_t

namespace meta17 {

namespace trait {

template<template<class...> class, class>
struct IsTypeTemplate : ::meta17::False {};

template<template<class...> class Template, class... Ts>
struct IsTypeTemplate<Template, Template<Ts...>> : ::meta17::True {};

} // namespace trait

template<class T, template<class...> class Template>
using IsTypeTemplate = trait::IsTypeTemplate<Template, std::remove_const_t<T>>;

} // namespace meta17
