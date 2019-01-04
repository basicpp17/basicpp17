#pragma once
#include "Const.h"

#include <type_traits> // common_type_t / enable_if

namespace meta17 {

/// Comparison and Ordering
// we use the commontype to work around (bool < int) issue
#define BOOL_OP(OP)                                                                                                    \
    template<auto A, auto B>                                                                                           \
    constexpr bool operator OP(Const<A>, Const<B>) {                                                                   \
        using T = std::common_type_t<decltype(A), decltype(B)>;                                                        \
        return static_cast<T>(A) OP static_cast<T>(B);                                                                 \
    }                                                                                                                  \
    template<auto A, class B, class = std::enable_if_t<std::is_integral_v<B>>>                                         \
    constexpr bool operator OP(Const<A>, B b) {                                                                        \
        using T = std::common_type_t<decltype(A), B>;                                                                  \
        return static_cast<T>(A) OP static_cast<T>(b);                                                                 \
    }                                                                                                                  \
    template<class A, auto B, class = std::enable_if_t<std::is_integral_v<A>>>                                         \
    constexpr bool operator OP(A a, Const<B>) {                                                                        \
        using T = std::common_type_t<A, decltype(B)>;                                                                  \
        return static_cast<T>(a) OP static_cast<T>(B);                                                                 \
    }

BOOL_OP(==)
BOOL_OP(!=)
BOOL_OP(<)
BOOL_OP(>)
BOOL_OP(<=)
BOOL_OP(>=)

#undef BOOL_OP

/// Calculations
//#define CALC_OP(OP) \
//    template<auto A, auto B> \
//    constexpr auto operator OP(Const<A>, Const<B>)->Const<A OP B> { \
//        return {}; \
//    }

// MSVC 2017 14.16.27023 cannot compile [auto]*[auto]
// this is a simple workaround:
#define CALC_OP(OP)                                                                                                    \
    template<auto A, auto B>                                                                                           \
    constexpr auto operator OP(Const<A>, Const<B>) /**/                                                                \
        ->Const<static_cast<decltype(A)>(A) OP static_cast<decltype(B)>(B)> {                                          \
        return {};                                                                                                     \
    }

CALC_OP(+)
CALC_OP(-)
CALC_OP(*)
CALC_OP(/)
CALC_OP(%)

#undef CALC_OP

} // namespace meta17
