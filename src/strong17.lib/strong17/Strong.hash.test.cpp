#include "Strong.hash.h"

#include "Strong.base.h"
#include "Strong.opaque.h"

#include <gtest/gtest.h>

using namespace strong17;

using PositionExplicit = Strong<int, struct PositionTag>;

STRONG_OPAQUE(PositionOpaque, int, struct PositionTag);

TEST(Strong, hasher) {
    static_assert(std::is_assignable_v<Hasher<PositionExplicit>, std::hash<PositionExplicit>>);
    static_assert(std::is_assignable_v<Hasher<PositionExplicit>, std::hash<Base<PositionExplicit>>>);

    // not possible due to missing Base extraction
    static_assert(!std::is_assignable_v<Hasher<PositionExplicit>, std::hash<PositionOpaque>>);
    static_assert(std::is_assignable_v<Hasher<PositionExplicit>, std::hash<Base<PositionOpaque>>>);
}

TEST(StrongOpaque, hasher) {
    static_assert(std::is_assignable_v<Hasher<PositionOpaque>, std::hash<PositionExplicit>>);
    static_assert(std::is_assignable_v<Hasher<PositionOpaque>, std::hash<Base<PositionExplicit>>>);

    // not possible due to missing Base extraction
    static_assert(!std::is_assignable_v<Hasher<PositionOpaque>, std::hash<PositionOpaque>>);
    static_assert(std::is_assignable_v<Hasher<PositionOpaque>, std::hash<Base<PositionOpaque>>>);
}
