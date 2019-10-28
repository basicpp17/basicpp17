#pragma once
#include "Tuple.h"

#include <utility> // std::declval

namespace tuple17 {

template<class... Ts, template<class...> class Template>
auto mapTemplateToTuple(Template<Ts...>) -> Tuple<Ts...>;

template<class P>
using MakeTuple = decltype(mapTemplateToTuple(std::declval<P>()));

} // namespace tuple17
