#pragma once

#include "None.h"

namespace meta17 {

/// Comparison and Ordering
#define BOOL_OP(OP)                                                                                                    \
    constexpr bool operator OP(const None&, const None&) { return true; }

/// TODO(mstaff): this is copied from a previous implementation. Thus, some questions arise:
/// Should all of these operators be implemented
/// Should all of these operators return true or should we treat all Nones as equal?
///

BOOL_OP(==)
BOOL_OP(!=)
BOOL_OP(<)
BOOL_OP(>)
BOOL_OP(<=)
BOOL_OP(>=)

#undef BOOL_OP

} // namespace meta17
