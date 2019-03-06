#include "Strong.make.h"

#include "Strong.opaque.h"

#include <meta17/Type.ops.h>

#include <gtest/gtest.h>

using namespace strong17;

struct PositionTag;
using PositionExplicit = Strong<int, PositionTag>;

STRONG_OPAQUE(PositionOpaque, int, PositionTag);

TEST(Strong, make) {
    static_assert(makeStrongType<int, PositionTag>() == type<PositionExplicit>);
    static_assert(make_strong_type<int, TypePack<PositionTag>> == type<PositionExplicit>);
    static_assert(std::is_same_v<MakeStrong<int, TypePack<PositionTag>>, PositionExplicit>);
}

TEST(StrongOpaque, make) {
    static_assert(makeOpaqueType(type<Strong<int, PositionTag>>) == type<PositionOpaque>);
    static_assert(make_opaque_type<Strong<int, PositionTag>> == type<PositionOpaque>);
    static_assert(std::is_same_v<MakeOpaque<Strong<int, PositionTag>>, PositionOpaque>);
}
