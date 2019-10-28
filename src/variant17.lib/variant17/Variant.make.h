#pragma once
#include "Variant.h"

#include <utility> // std::declval

namespace variant17 {

template<class... Ts, template<class...> class Template>
auto mapTemplateToVariant(Template<Ts...>) -> Variant<Ts...>;

template<class P>
using MakeVariant = decltype(mapTemplateToVariant(std::declval<P>()));

} // namespace variant17
