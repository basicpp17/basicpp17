#pragma once

namespace meta17 {

/// Transport a pack of types
template<class...>
struct TypePack {};

template<class... Ts>
constexpr auto type_pack = TypePack<Ts...>{};

} // namespace meta17
