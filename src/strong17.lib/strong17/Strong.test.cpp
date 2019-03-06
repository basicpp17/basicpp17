#include "Strong.h"
#include "Strong.manip.h"
#include "Strong.opaque.h"
#include "Strong.ops.h"
#include "Strong.ostream.h"

#include <gtest/gtest.h>

using namespace strong17;

using Position = Strong<int, struct PositionTag>;
using Distance = Strong<int, struct DistanceTag>;

auto operator+(Position a, Distance d) -> Position { return Position{a.v + d.v}; }

TEST(Strong, usage) {
    auto p = Position{};
    EXPECT_EQ(p.v, 0);

    auto d = Distance{1};
    EXPECT_EQ(d.v, 1);

    auto r = p + d;
    EXPECT_EQ(r.v, 1);
}

STRONG_OPAQUE(PositionOpaque, int, struct PositionTag);
STRONG_OPAQUE(DistanceOpaque, int, struct DistanceTag);

auto operator+(PositionOpaque a, DistanceOpaque d) -> PositionOpaque { return PositionOpaque{a.v + d.v}; }

TEST(StrongOpaque, usage) {
    auto p = PositionOpaque{};
    EXPECT_EQ(p.v, 0);

    auto d = DistanceOpaque{1};
    EXPECT_EQ(d.v, 1);

    auto r = p + d;
    EXPECT_EQ(r.v, 1);
}
