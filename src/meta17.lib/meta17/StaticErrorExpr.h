#pragma once
#include "Type.h"

namespace meta17 {

template<class T, class F>
struct StaticAssertExpr {
    Type<T> t;
    F f;

    constexpr operator T() const {
        f();
        return {};
    }
};
template<class T, class F>
StaticAssertExpr(Type<T>, F &&)->StaticAssertExpr<T, F>;

// embed a static_assert error as an expression of type T
#define META17_STATIC_ERROR_EXPR(T, error)                                                                             \
    [](auto v) -> T {                                                                                                  \
        static_assert(sizeof(v) == 0, error);                                                                          \
        return {};                                                                                                     \
    }(false)

#define META17_STATIC_ASSERT_EXPR(T, cond, error)                                                                      \
    []() -> T {                                                                                                        \
        static_assert(cond, error);                                                                                    \
        return {};                                                                                                     \
    }()

} // namespace meta17
