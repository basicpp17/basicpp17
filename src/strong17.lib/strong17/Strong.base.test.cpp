#include "Strong.base.h"

#include "Strong.opaque.h"

#include <gtest/gtest.h>

using namespace strong17;

using PositionExplicit = Strong<int, struct PositionTag>;

STRONG_OPAQUE(PositionOpaque, int, struct PositionTag);

TEST(Strong, base) {
    static_assert(std::is_same_v<Base<PositionExplicit>, PositionExplicit>);
    static_assert(!std::is_same_v<Base<PositionExplicit>, int>);
    static_assert(!std::is_same_v<Base<PositionExplicit>, struct PositionTag>);
}

TEST(StrongOpaque, base) {
    static_assert(std::is_same_v<Base<PositionOpaque>, PositionExplicit>);
    static_assert(!std::is_same_v<Base<PositionOpaque>, struct PositionTag>);
    static_assert(!std::is_same_v<Base<PositionOpaque>, char>);

    static_assert(std::is_same_v<Base<PositionOpaque>, Base<PositionExplicit>>);
}
