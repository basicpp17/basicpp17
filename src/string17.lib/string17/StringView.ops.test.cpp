#include "StringView.h"
#include "StringView.ops.h"
#include "StringView.ostream.h"
#include "viewCString.h"
#include "viewLiteral.h"

#include <gtest/gtest.h>

using namespace string17;

TEST(StringViewOps, simple) {
    constexpr auto x = viewLiteral("Hello");
    constexpr auto y = viewCString("Hello");

    EXPECT_EQ(x, y);
}
