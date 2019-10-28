#include "Strong.extract.h"

#include "Strong.base.h"
#include "Strong.opaque.h"

#include "meta17/same.h"

#include <gtest/gtest.h>

using namespace strong17;
using meta17::same;

using PositionExplicit = Strong<int, struct PositionTag>;

STRONG_OPAQUE(PositionOpaque, int, struct PositionTag);

TEST(Strong, extractValue) {
    static_assert(same<ExtractValue<PositionExplicit>, int>);
    static_assert(!same<ExtractValue<PositionExplicit>, struct PositionTag>);
    static_assert(!same<ExtractValue<PositionExplicit>, char>);
    // ExtractValue is only defined on Strong!
    // static_assert(!same<ExtractValue<int>, int>);
}

TEST(StrongOpaque, extractValue) {
    static_assert(same<ExtractValue<Base<PositionOpaque>>, int>);
    static_assert(!same<ExtractValue<Base<PositionOpaque>>, struct PositionTag>);
    static_assert(!same<ExtractValue<Base<PositionOpaque>>, char>);
}
