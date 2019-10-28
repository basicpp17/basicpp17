#pragma once

namespace meta17 {

/// true only if given type is a template of values
template<class T>
constexpr auto is_template_of_values = false;

template<auto... Vs, template<auto...> class Template>
constexpr auto is_template_of_values<Template<Vs...>> = true;

/// true only if given type is the given template
template<class T, template<auto...> class Template>
constexpr auto is_value_template = false;

template<auto... Vs, template<auto...> class Template>
constexpr auto is_value_template<Template<Vs...>, Template> = true;

} // namespace meta17
