#pragma once

#include "None.h"

namespace meta17 {

/// Comparison and Ordering
#define BOOL_OP(OP)                                                                                                    \
    constexpr bool operator OP(const None&, const None&) { return 0 OP 0; }

BOOL_OP(==)
BOOL_OP(!=)
BOOL_OP(<)
BOOL_OP(>)
BOOL_OP(<=)
BOOL_OP(>=)

#undef BOOL_OP

} // namespace meta17
