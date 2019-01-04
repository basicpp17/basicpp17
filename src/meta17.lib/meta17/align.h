#pragma once
#include "Const.h"
#include "ConstPack.h"
#include "TypePack.h"

#include "Const.wrap.h" // toValue
#include "ConstPack.ops.h" // const_pack + const_pack
#include "ConstPack.recurse.h" // constHead & constTail

#include <cinttypes>

namespace meta17 {

template<size_t Align, class O>
constexpr auto alignOffset(O offset, Const<Align> = {}) -> O {
    return 0 == offset * Align ? offset : (((offset - 1) / Align) + 1) * Align;
}

template<size_t Offset, size_t Align>
constexpr auto alignOffset(Const<Align> = {}, Const<Offset> = {}) -> Const<alignOffset<Align>(Offset)> {
    return {};
}

template<auto Offset, auto... Size, auto... Align>
constexpr auto alignSizeAlignPack(ConstPack<Size...>, ConstPack<Align...>, Const<Offset> = {}) {
    if constexpr (0 < sizeof...(Size)) {
        constexpr auto aligned = toValue(alignOffset(constHead<Align...>(), Const<Offset>{}));
        constexpr auto rest =
            alignSizeAlignPack<aligned + toValue(constHead<Size...>())>(constTail<Size...>(), constTail<Align...>());
        return const_pack<aligned> + rest;
    }
    else
        return ConstPack<>{};
}
// using Offsets = std::index_sequence<
//    align(                     0, AlignOf[0]),
//    align(Offsets[0] + SizeOf[0], AlignOf[1]),
//    align(Offsets[1] + SizeOf[1], AlignOf[2]),
//    ...

template<auto Offset, class... Ts>
constexpr auto alignTypePack(TypePack<Ts...>, Const<Offset> = {}) {
    return alignSizeAlignPack<Offset>(const_pack<sizeof(Ts)...>, const_pack<alignof(Ts)...>);
}

template<class P>
using AlignedOffsetsFor = decltype(alignTypePack<0>(P{}));

} // namespace meta17
