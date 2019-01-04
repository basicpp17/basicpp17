#pragma once
#include "TemplateOfTypes.h"

#include <type_traits> // std::remove_const_t

namespace meta17 {

/// Unwrapping
namespace details {

template<class, class>
struct Unwrap;

template<class T, template<class...> class Template>
struct Unwrap<T, TemplateOfTypes<Template>> {
    using Return = T;
};
template<class T, template<class...> class Template>
struct Unwrap<Template<T>, TemplateOfTypes<Template>> {
    using Return = T;
};

} // namespace details

template<class T, class Template>
using UnwrapTemplate = typename details::Unwrap<std::remove_const_t<T>, Template>::Return;

/// Wrapping
namespace details {

template<class, class...>
struct Wrap;

template<template<class...> class Template, class... Ts>
struct Wrap<TemplateOfTypes<Template>, Ts...> {
    using Return = Template<Ts...>;
};
template<template<class...> class Template, class... Ts>
struct Wrap<TemplateOfTypes<Template>, Template<Ts...>> {
    using Return = Template<Ts...>;
};

} // namespace details

template<class Template, class... Ts>
using ToTemplate = typename details::Wrap<Template, Ts...>::Return;

} // namespace meta17
