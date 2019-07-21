#include "Strong.h"
#include "Strong.manip.h"
#include "Strong.opaque.h"
#include "Strong.ops.h"
#include "Strong.ostream.h"
#include "Strong.trait.h"

#include "meta17/Bool.h"

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

TEST(Strong, nesting) {
    (void)Strong<int, struct SomeTag>{};
    //(void)Strong<Position, struct SomeTag>{}; // <- should not compile
    //(void)Strong<PositionOpaque, struct SomeTag>{}; // <- should not compile

    static_assert(checkStrongArgs<int, struct SomeTag>());
    static_assert(!checkStrongArgs<Position, struct SomeTag>());
    static_assert(!checkStrongArgs<PositionOpaque, struct SomeTag>());
}

struct Incomplete;
struct EmptyComplete {};
struct SizedComplete {
    int x;
};

TEST(Strong, value) {
    (void)Strong<SizedComplete, struct SomeTag>{};
    (void)Strong<EmptyComplete, struct SomeTag>{};
    // (void)Strong<Incomplete, struct SomeTag>{}; // <- should not compile

    static_assert(checkStrongArgs<SizedComplete, struct SomeTag>());
    static_assert(checkStrongArgs<EmptyComplete, struct SomeTag>());
    // static_assert(checkStrongArgs<Incomplete, struct SomeTag>()); // no static_assert necessary!
}

TEST(Strong, tags) {
    (void)Strong<int, Incomplete>{};
    (void)Strong<int, EmptyComplete>{};
    // (void)Strong<int, int>{}; // <- should not compile
    // (void)Strong<int, SizedComplete>{}; // <- should not compile

    static_assert(checkStrongArgs<int, Incomplete>());
    static_assert(checkStrongArgs<int, EmptyComplete>());
    static_assert(!checkStrongArgs<int, int>());
    static_assert(!checkStrongArgs<int, SizedComplete>());
}
