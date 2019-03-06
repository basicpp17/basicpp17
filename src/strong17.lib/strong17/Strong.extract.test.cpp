#include "Strong.extract.h"

#include "Strong.base.h"
#include "Strong.opaque.h"

#include <gtest/gtest.h>

using namespace strong17;

using PositionExplicit = Strong<int, struct PositionTag>;

STRONG_OPAQUE(PositionOpaque, int, struct PositionTag);

TEST(Strong, extractValue) {
    static_assert(std::is_same_v<ExtractValue<PositionExplicit>, int>);
    static_assert(!std::is_same_v<ExtractValue<PositionExplicit>, struct PositionTag>);
    static_assert(!std::is_same_v<ExtractValue<PositionExplicit>, char>);
    // ExtractValue is only defined on Strong!
    // static_assert(!std::is_same_v<ExtractValue<int>, int>);
}

TEST(StrongOpaque, extractValue) {
    static_assert(std::is_same_v<ExtractValue<Base<PositionOpaque>>, int>);
    static_assert(!std::is_same_v<ExtractValue<Base<PositionOpaque>>, struct PositionTag>);
    static_assert(!std::is_same_v<ExtractValue<Base<PositionOpaque>>, char>);
}
