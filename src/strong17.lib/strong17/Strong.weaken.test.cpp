#include "Strong.weaken.h"

#include "Strong.opaque.h"

#include "meta17/Type.ops.h"
#include "meta17/same.h"

#include <gtest/gtest.h>

using namespace strong17;
using meta17::same;

struct PositionTag;
using PositionExplicit = Strong<int, PositionTag>;

STRONG_OPAQUE(PositionOpaque, int, PositionTag);

TEST(Strong, weakenType) {
    static_assert(weakenType<PositionExplicit>() == type<int>);
    static_assert(weaken_type<PositionExplicit> == type<int>);
    static_assert(same<WeakenType<PositionExplicit>, Type<int>>);
    static_assert(weaken(PositionExplicit{0}) == 0);
}

TEST(StrongOpaque, weakenType) {
    static_assert(weakenType<PositionOpaque>() == type<int>);
    static_assert(weaken_type<PositionOpaque> == type<int>);
    static_assert(same<WeakenType<PositionOpaque>, Type<int>>);
    static_assert(weaken(PositionOpaque{0}) == 0);
}

TEST(StrongMixed, weakenType) { //
    static_assert(weaken(0) == 0);
}
