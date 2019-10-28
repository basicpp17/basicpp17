#pragma once
#include "IndexPack.h"

#include "IndexPack.extract.h"
#include "TypePack.h"

#include <utility> // std::index_sequence_for

namespace meta17 {

/// type_pack<A, B, C,...> -> index_pack<0, 1, 2, ...>
template<class... Ts, template<typename...> class Template>
constexpr auto indexPackFor(Template<Ts...> = {}) {
    return extract_index_pack<std::index_sequence_for<Ts...>>;
}

/// const_pack<9, 8, 7, ...> -> index_pack<0, 1, 2, ...>
template<auto... Vs, template<auto...> class Template>
constexpr auto indexPackFor(Template<Vs...> = {}) {
    return extract_index_pack<std::make_index_sequence<sizeof...(Vs)>>;
}

template<class T>
constexpr auto index_pack_for = index_pack<>;

/// TypePack<A, B, C,...> -> index_pack<0, 1, 2, ...>
template<class... Ts, template<typename...> class Template>
constexpr auto index_pack_for<Template<Ts...>> = extract_index_pack<std::index_sequence_for<Ts...>>;

/// ConstPack<9, 8, 7, ...> -> index_pack<0, 1, 2, ...>
template<auto... Vs, template<auto...> class Template>
constexpr auto index_pack_for<Template<Vs...>> = extract_index_pack<std::make_index_sequence<sizeof...(Vs)>>;

template<class P>
using IndexPackFor = std::remove_const_t<decltype(index_pack_for<P>)>;

} // namespace meta17
