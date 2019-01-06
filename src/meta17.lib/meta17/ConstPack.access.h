#pragma once
#include "ConstPack.h"

#include "Index.h"
#include "IndexPack.h"

#include "Const.ops.h" // index - index
#include "ConstPack.recurse.h" // count
#include "IndexPack.for.h" // IndexPackFor

#include <cstddef> // size_t

namespace meta17 {

template<size_t I, auto... Vs, size_t... Is>
constexpr auto constAt(ConstPack<Vs...> = {}, IndexPack<Is...> = {}, Index<I> = {}) {
    return Const<((I == Is ? Vs : 0) + ... + 0)>{};
}

template<class P, class I>
constexpr auto constAt(P = {}, I = {}) {
    using IP = IndexPackFor<P>;
    return constAt(P{}, IP{}, I{});
}

template<class P, class I>
using ConstAt = decltype(constAt<P, I>());

template<class P, class IP>
constexpr auto constLast(P = {}, IP = {}) {
    constexpr auto lastIndex = index<constCount(P{})> - index<1>;
    return constAt(P{}, IP{}, lastIndex);
}

template<class P>
constexpr auto constLast(P = {}) {
    using IP = IndexPackFor<P>;
    return constLast<P, IP>();
}

template<class P>
using ConstLast = decltype(constLast<P>());

} // namespace meta17
