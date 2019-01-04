#pragma once
#include "IndexTypePack.h"

#include "Const.ops.h" // const + const
#include "Index.h"
#include "IndexType.extract.h" // extract_index
#include "IndexType.trait.h" // is_index_type
#include "Type.wrap.h" // UnwrapType
#include "TypePack.recurse.h" // type_count & type_tail

namespace meta17 {

template<class... Ts, size_t I = 0>
constexpr auto makeIndexTypePack(TypePack<Ts...> = {}, Index<I> = {}) {
    using P = TypePack<Ts...>;
    if constexpr (type_count<P> == 0) {
        return TypePack{};
    }
    else {
        auto recurse = [](auto it) {
            using IT = decltype(it);
            constexpr auto next = extract_index<IT> + index<1>;
            return TypePack<IT>{} + makeIndexTypePack(type_tail<P>, next);
        };
        using H = UnwrapType<TypeHead<P>>;
        if constexpr (is_index_type<H>)
            return recurse(H{});
        else
            return recurse(IndexType<I, H>{});
    }
}

template<class P>
using MakeIndexTypePack = decltype(makeIndexTypePack(P{}));

template<class P>
constexpr auto make_index_type_pack = MakeIndexTypePack<P>{};

} // namespace meta17
