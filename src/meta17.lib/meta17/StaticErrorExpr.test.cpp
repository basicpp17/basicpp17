#include "StaticErrorExpr.h"

using namespace meta17;

template<auto, auto>
constexpr int a = META17_STATIC_ERROR_EXPR(int, "missed");

template<auto X>
constexpr int a<X, X> = X == 1 ? X : META17_STATIC_ASSERT_EXPR(int, X == 1, "wrong");

void testStaticError() {
    //    a<2, 3>; // triggers "missed"
    //    a<2, 2>; // triggers "wrong"
    static_assert(1 == a<1, 1>); //
}
