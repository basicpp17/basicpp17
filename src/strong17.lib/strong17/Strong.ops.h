#pragma once
#include "Strong.h"

namespace strong17 {

/// Comparison and Ordering
#define BOOL_OP(OP)                                                                                                    \
    template<class A_T, class... A_Tags, class B_T, class... B_Tags>                                                   \
    constexpr bool operator OP(Strong<A_T, A_Tags...> a, Strong<B_T, B_Tags...> b) {                                   \
        return a.v OP b.v;                                                                                             \
    }

BOOL_OP(==)
BOOL_OP(!=)
BOOL_OP(<)
BOOL_OP(>)
BOOL_OP(<=)
BOOL_OP(>=)

#undef BOOL_OP

} // namespace strong17
