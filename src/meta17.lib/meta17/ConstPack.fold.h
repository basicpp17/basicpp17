#pragma once
#include "ConstPack.h"

#include <algorithm> // std::max

namespace meta17 {

template<auto... Vs>
constexpr auto max(ConstPack<Vs...> = {}) {
    return std::max({Vs...});
}

} // namespace meta17
