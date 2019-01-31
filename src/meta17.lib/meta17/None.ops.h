#pragma once

#include "None.h"

namespace meta17 {

/// Comparison and Ordering
#define BOOL_OP_TRUE(OP)                                                                                               \
    constexpr bool operator OP(const None&, const None&) { return true; }

/// Comparison and Ordering
#define BOOL_OP_FALSE(OP)                                                                                              \
    constexpr bool operator OP(const None&, const None&) { return false; }

BOOL_OP_TRUE(==)
BOOL_OP_FALSE(!=)
BOOL_OP_FALSE(<)
BOOL_OP_FALSE(>)
BOOL_OP_TRUE(<=)
BOOL_OP_TRUE(>=)

#undef BOOL_OP_TRUE
#undef BOOL_OP_FALSE

} // namespace meta17
