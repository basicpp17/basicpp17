#include "Strong.trait.h"

#include "Strong.base.h"
#include "Strong.opaque.h"

#include <gtest/gtest.h>

using namespace strong17;

using PositionExplicit = Strong<int, struct PositionTag>;

STRONG_OPAQUE(PositionOpaque, int, struct PositionTag);

TEST(StrongMixed, is_strong) {
    static_assert(is_strong<PositionOpaque>);
    static_assert(is_strong<PositionExplicit>);
    static_assert(!is_strong<int>);
    static_assert(!is_strong<struct PositionTag>);
}

TEST(StrongMixed, is_opaque) {
    static_assert(is_opaque<PositionOpaque>);
    static_assert(!is_opaque<PositionExplicit>);
    static_assert(is_strong<Base<PositionOpaque>>);
    static_assert(is_strong<PositionOpaque>);
}
