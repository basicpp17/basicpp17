#pragma once

#include "TemplateOfTypes.h"

#include "Bool.wrap.h"
#include "Type.h"

#include <type_traits> // std::remove_const_t

namespace meta17 {

/// true only if given type is a template of types
template<class T>
constexpr auto is_template_of_types = false;

template<class... Ts, template<class...> class Template>
constexpr auto is_template_of_types<Template<Ts...>> = true;

/// true only if given type is the given template
template<class T, template<class...> class Template>
constexpr auto is_type_template = false;

template<class... Vs, template<class...> class Template>
constexpr auto is_type_template<Template<Vs...>, Template> = true;

} // namespace meta17
