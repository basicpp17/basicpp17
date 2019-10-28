#include "strong17/Strong.base.h"

#include "meta17/same.h"
#include "strong17/Strong.opaque.h"

#include <gtest/gtest.h>

using namespace strong17;
using meta17::same;

using PositionExplicit = Strong<int, struct PositionTag>;

STRONG_OPAQUE(PositionOpaque, int, struct PositionTag);

TEST(Strong, base) {
    static_assert(same<Base<PositionExplicit>, PositionExplicit>);
    static_assert(!same<Base<PositionExplicit>, int>);
    static_assert(!same<Base<PositionExplicit>, struct PositionTag>);
}

TEST(StrongOpaque, base) {
    static_assert(same<Base<PositionOpaque>, PositionExplicit>);
    static_assert(!same<Base<PositionOpaque>, struct PositionTag>);
    static_assert(!same<Base<PositionOpaque>, char>);

    static_assert(same<Base<PositionOpaque>, Base<PositionExplicit>>);
}
