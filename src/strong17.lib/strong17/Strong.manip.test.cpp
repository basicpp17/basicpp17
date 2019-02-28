#include "Strong.h"

#include "Strong.manip.h"

#include <gtest/gtest.h>

using namespace strong17;

using Position = Strong<int, struct PositionTag>;
using Distance = Strong<int, struct DistanceTag>;

TEST(Strong, manip) {
    static_assert(type<AddStrongTags<TypePack<>, Position>> == type<Position>);

    static_assert(
        type<AddStrongTags<TypePack<struct ComputedTag, struct UnusedTag>, Position>> ==
        type<Strong<int, PositionTag, ComputedTag, UnusedTag>>);

    static_assert(type<AddStrongTag<DistanceTag, RemoveStrongTag<PositionTag, Position>>> == type<Distance>);
    static_assert(type<ChangeStrongValue<float, Position>> == type<Strong<float, PositionTag>>);
    static_assert(type<ReplaceStrongTag<PositionTag, DistanceTag, Position>> == type<Distance>);
}
