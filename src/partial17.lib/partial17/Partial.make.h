#pragma once
#include "Partial.h"

#include <utility> // std::declval

namespace partial17 {

template<class... Ts, template<class...> class Template>
auto mapTemplateToPartial(Template<Ts...>) -> Partial<Ts...>;

template<class TT>
using MakePartial = decltype(mapTemplateToPartial(std::declval<TT>()));

} // namespace partial17
