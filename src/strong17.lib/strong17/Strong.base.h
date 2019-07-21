#pragma once

namespace strong17 {

template<class V, class...>
struct Strong;

/// Allows to peek through the inheritance of an OPAQUE Strong
/// note: fails to compile for non-Strong types
template<class V, class... Tags>
auto base(Strong<V, Tags...>) -> Strong<V, Tags...>;

template<class T>
using Base = decltype(base(T{}));

} // namespace strong17

#include "Strong.trait.h"
