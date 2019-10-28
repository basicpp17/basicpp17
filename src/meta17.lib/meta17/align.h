#pragma once
#include "Const.h"
#include "ConstPack.h"
#include "TypePack.h"

#include "Const.wrap.h" // to_value
#include "ConstPack.ops.h" // const_pack + const_pack
#include "ConstPack.recurse.h" // constHead & constTail
#include "ConstPack.sizeof.h" // sizeof_pack, alignof_pack

#include <cinttypes>

namespace meta17 {

// workaround: MSVC2017 needs the static_cast in cases where O = size_t
template<size_t align, size_t offset>
constexpr auto align_offset = static_cast<size_t>(((offset + align - 1) / align) * align);

/// note: runtime version only supports 2^n alignments
template<size_t align, class T>
constexpr auto alignOffset(T offset) -> T {
    static_assert(((align ^ (align - 1)) & (align - 1)) == (align - 1), "power of 2 alignments!");
    return static_cast<T>((offset + align - 1) & ~(align - 1));
}

template<size_t Offset, class SizePack, class AlignPack>
constexpr auto align_size_align_pack = [] {
    constexpr auto aligned = align_offset<const_head<AlignPack>, Offset>;
    constexpr auto rest =
        align_size_align_pack<aligned + const_head<SizePack>, ConstTail<SizePack>, ConstTail<AlignPack>>;
    return const_pack<aligned> + rest;
}();

template<size_t Offset>
constexpr auto align_size_align_pack<Offset, ConstPack<>, ConstPack<>> = const_pack<>;

// using Offsets = ConstPack<
//    align(                     0, AlignOf[0]),
//    align(Offsets[0] + SizeOf[0], AlignOf[1]),
//    align(Offsets[1] + SizeOf[1], AlignOf[2]),
//    ...

/// creates ConstPack that contains the offset of all members of a Ts tuple
template<size_t Offset, class TP>
constexpr auto align_type_pack = align_size_align_pack<Offset, SizeofPack<TP>, AlignofPack<TP>>;

template<size_t Offset = 0, class TP>
constexpr auto alignTypePack(TP) {
    return align_type_pack<Offset, TP>;
}

/// size of Offset + sizePack aligned as alignPack
template<size_t Offset, class SizePack, class AlignPack>
constexpr auto sizeof_size_aligned_pack = sizeof_size_aligned_pack<
    align_offset<const_head<AlignPack>, Offset> + const_head<SizePack>,
    ConstTail<SizePack>,
    ConstTail<AlignPack>>;

template<size_t Offset>
constexpr auto sizeof_size_aligned_pack<Offset, ConstPack<>, ConstPack<>> = Offset;

/// size of all members of a Ts tuple
template<size_t Offset, class TP>
constexpr auto sizeof_type_pack = sizeof_size_aligned_pack<Offset, SizeofPack<TP>, AlignofPack<TP>>;

template<size_t Offset = 0, class TP>
constexpr auto sizeofTypePack(TP) {
    return sizeof_type_pack<Offset, TP>;
}

template<class P>
using AlignedOffsetsFor = decltype(align_type_pack<0, P>);

template<class... Ts>
constexpr auto maxAlignOf() {
    auto r = size_t{1};
    ((alignof(Ts) > r ? (r = alignof(Ts), 0) : 0), ...);
    return r;
}

} // namespace meta17
