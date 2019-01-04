#include "Strong.h"
#include "Strong.manip.h"
#include "Strong.ops.h"
#include "Strong.ostream.h"

#include <gtest/gtest.h>

using namespace strong17;

using Pos = Strong<int, struct PosTag>;
using Dist = Strong<int, struct DistTag>;

auto operator+(Pos a, Dist d) -> Pos { return Pos{a.v + d.v}; }

TEST(Strong, basic) {
    auto x = Pos{};
    ASSERT_EQ(x.v, 0);

    auto d = Dist{1};
    // ASSERT_NE(x, d); // no compile
    ASSERT_EQ(d.v, 1);

    auto y = x + d;
    ASSERT_NE(x, y);
    // ASSERT_EQ(x, y); // fail - use ostream
    ASSERT_EQ(y.v, 1);
}

TEST(Strong, manip) {
    static_assert(type<AddStrongTags<TypePack<>, Pos>> == type<Pos>);

    static_assert(
        type<AddStrongTags<TypePack<struct ComputedTag, struct UnusedTag>, Pos>> ==
        type<Strong<int, PosTag, ComputedTag, UnusedTag>>);

    static_assert(type<AddStrongTag<DistTag, RemoveStrongTag<PosTag, Pos>>> == type<Dist>);
    static_assert(type<ChangeStrongValue<float, Pos>> == type<Strong<float, PosTag>>);
    static_assert(type<ReplaceStrongTag<PosTag, DistTag, Pos>> == type<Dist>);
}
