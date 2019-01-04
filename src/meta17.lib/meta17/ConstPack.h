#pragma once

namespace meta17 {

/// store a pack of constants
template<auto...>
struct ConstPack {};

template<auto... Vs>
constexpr auto const_pack = ConstPack<Vs...>{};

} // namespace meta17
