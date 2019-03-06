#include "Strong.ops.h"

#include "Strong.opaque.h"

#include <gtest/gtest.h>

using namespace strong17;

using PositionExplicit = Strong<int, struct PositionTag>;
using DistanceExplicit = Strong<int, struct DistanceTag>;

STRONG_OPAQUE(PositionOpaque, int, struct PositionTag);
STRONG_OPAQUE(DistanceOpaque, int, struct DistanceTag);

TEST(Strong, ops) {
    auto p1 = PositionExplicit{0};
    auto p2 = PositionExplicit{2};
    auto d1 = DistanceExplicit{1};
    auto d2 = DistanceExplicit{1};
    EXPECT_FALSE(p1 == p2);
    EXPECT_TRUE(p1 != p2);
    EXPECT_TRUE(p1 <= p2);
    EXPECT_FALSE(p1 >= p2);
    EXPECT_TRUE(p1 < p2);
    EXPECT_FALSE(p1 > p2);
    EXPECT_TRUE(d1 == d2);
    EXPECT_FALSE(d1 != d2);
    EXPECT_TRUE(d1 <= d2);
    EXPECT_TRUE(d1 >= d2);
    EXPECT_FALSE(d1 < d2);
    EXPECT_FALSE(d1 > d2);
}

TEST(StrongOpaque, ops) {
    auto p1 = PositionOpaque{0};
    auto p2 = PositionOpaque{2};
    auto d1 = DistanceOpaque{1};
    auto d2 = DistanceOpaque{1};
    EXPECT_FALSE(p1 == p2);
    EXPECT_TRUE(p1 != p2);
    EXPECT_TRUE(p1 <= p2);
    EXPECT_FALSE(p1 >= p2);
    EXPECT_TRUE(p1 < p2);
    EXPECT_FALSE(p1 > p2);
    EXPECT_TRUE(d1 == d2);
    EXPECT_FALSE(d1 != d2);
    EXPECT_TRUE(d1 <= d2);
    EXPECT_TRUE(d1 >= d2);
    EXPECT_FALSE(d1 < d2);
    EXPECT_FALSE(d1 > d2);
}

TEST(StrongMixed, ops) {
    auto p1 = PositionExplicit{0};
    auto p2 = PositionOpaque{2};
    auto d1 = DistanceExplicit{1};
    auto d2 = DistanceOpaque{1};
    EXPECT_FALSE(p1 == p2);
    EXPECT_TRUE(p1 != p2);
    EXPECT_TRUE(p1 <= p2);
    EXPECT_FALSE(p1 >= p2);
    EXPECT_TRUE(p1 < p2);
    EXPECT_FALSE(p1 > p2);
    EXPECT_TRUE(d1 == d2);
    EXPECT_FALSE(d1 != d2);
    EXPECT_TRUE(d1 <= d2);
    EXPECT_TRUE(d1 >= d2);
    EXPECT_FALSE(d1 < d2);
    EXPECT_FALSE(d1 > d2);
}
