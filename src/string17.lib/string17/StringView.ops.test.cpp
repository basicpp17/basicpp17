#include "StringView.h"
#include "StringView.ops.h"
#include "StringView.ostream.h"
#include "viewCString.h"
#include "viewLiteral.h"

#include <gtest/gtest.h>

using namespace string17;

TEST(StringViewOps, simple) {
    constexpr auto cx = viewLiteral("Hello");
    constexpr auto cy = viewCString("Hello");
    static_assert(cx == cy);

    auto x = viewLiteral("Hello");
    auto y = viewCString("Hello");
    EXPECT_EQ(x, y);
}
