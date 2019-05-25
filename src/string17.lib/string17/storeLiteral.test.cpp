#include "storeLiteral.h"

#include <gtest/gtest.h>

using namespace string17;

TEST(storeLiteral, basic) {
    constexpr auto x = storeLiteral("Hello");
    static_assert(x.size() == 5u);

    EXPECT_EQ(x.size(), 5u);
}
