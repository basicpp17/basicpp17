#include "Strong.opaque.h"

#include "Strong.base.h"
#include "Strong.hash.h"
#include "Strong.ops.h"
#include "Strong.ostream.h"
#include "Strong.trait.h"

#include <meta17/Type.ops.h>

#include <gtest/gtest.h>

using namespace strong17;

using PosRaw = Strong<int, struct PosTag>;

STRONG_OPAQUE(Pos, int, struct PosTag);
STRONG_OPAQUE(Dist, int, struct DistTag);

static_assert(is_strong<Pos>);
static_assert(!is_strong<int>);

static_assert(is_opaque<Pos>);
static_assert(!is_opaque<PosRaw>);

auto operator+(Pos a, Dist d) -> Pos { return Pos{a.v + d.v}; }

static_assert(std::is_assignable_v<Hasher<Pos>, std::hash<Base<Pos>>>);

static_assert(make_opaque_type<Strong<int, PosTag>> == type<Pos>);

TEST(StrongOpaque, basic) {
    auto x = Pos{};
    ASSERT_EQ(x.v, 0);

    auto d = Dist{1};
    // ASSERT_NE(x, d); // no compile
    ASSERT_EQ(d.v, 1);

    auto y = x + d;
    ASSERT_NE(x, y);
    // TODO(arBmind): ostream does not work :(
    // ASSERT_EQ(x, y); // fail - use ostream
    ASSERT_EQ(y.v, 1);
}
