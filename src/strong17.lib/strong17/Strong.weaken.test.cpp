#include "Strong.weaken.h"

#include "Strong.opaque.h"

#include <meta17/Type.ops.h>

#include <gtest/gtest.h>

using namespace strong17;

struct PositionTag;
using PositionExplicit = Strong<int, PositionTag>;

STRONG_OPAQUE(PositionOpaque, int, PositionTag);

TEST(Strong, weakenType) {
    static_assert(weakenType<PositionExplicit>() == type<int>);
    static_assert(weaken_type<PositionExplicit> == type<int>);
    static_assert(std::is_same_v<WeakenType<PositionExplicit>, Type<int>>);
    static_assert(weaken(PositionExplicit{0}) == 0);
}

TEST(StrongOpaque, weakenType) {
    static_assert(weakenType<PositionOpaque>() == type<int>);
    static_assert(weaken_type<PositionOpaque> == type<int>);
    static_assert(std::is_same_v<WeakenType<PositionOpaque>, Type<int>>);
    static_assert(weaken(PositionOpaque{0}) == 0);
}

TEST(StrongMixed, weakenType) { //
    static_assert(weaken(0) == 0);
}
