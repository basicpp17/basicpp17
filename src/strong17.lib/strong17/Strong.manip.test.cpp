#include "Strong.h"

#include "Strong.base.h"
#include "Strong.manip.h"
#include "Strong.opaque.h"

#include <gtest/gtest.h>

using namespace strong17;

using PositionExplicit = Strong<int, struct PositionTag>;
using DistanceExplicit = Strong<int, struct DistanceTag>;

TEST(Strong, manip) {
    static_assert(type<AddStrongTags<TypePack<>, PositionExplicit>> == type<PositionExplicit>);

    static_assert(
        type<AddStrongTags<TypePack<struct ComputedTag, struct UnusedTag>, PositionExplicit>> ==
        type<Strong<int, PositionTag, ComputedTag, UnusedTag>>);

    static_assert(
        type<AddStrongTag<DistanceTag, RemoveStrongTag<PositionTag, PositionExplicit>>> == type<DistanceExplicit>);
    static_assert(type<ChangeStrongValue<float, PositionExplicit>> == type<Strong<float, PositionTag>>);
    static_assert(type<ReplaceStrongTag<PositionTag, DistanceTag, PositionExplicit>> == type<DistanceExplicit>);
}

STRONG_OPAQUE(PositionOpaque, int, PositionTag);
STRONG_OPAQUE(DistanceOpaque, int, DistanceTag);

// TODO CK: Should it be possible to manipulate Opaque Strongs?
// TEST(StrongOpaque, manip) {
//    static_assert(type<AddStrongTags<TypePack<>, PositionOpaque>> == type<PositionOpaque>);

//    static_assert(
//        type<AddStrongTags<TypePack<struct ComputedTag, struct UnusedTag>, PositionOpaque>> ==
//        type<Strong<int, PositionTag, ComputedTag, UnusedTag>>);

//    static_assert(
//        type<AddStrongTag<DistanceTag, RemoveStrongTag<PositionTag, PositionOpaque>>> == type<DistanceOpaque>);
//    static_assert(type<ChangeStrongValue<float, PositionOpaque>> == type<Strong<float, PositionTag>>);
//    static_assert(type<ReplaceStrongTag<PositionTag, DistanceTag, PositionOpaque>> == type<DistanceOpaque>);
//}
