#include "StringStore.h"

#include <gtest/gtest.h>

using namespace string17;

TEST(StringStore, basic) {
    constexpr auto x = StringStore{"Hello"};
    static_assert(x[0] == 'H');
    static_assert(x.size() == 6); // 5 chars + '\0'
    static_assert(!x.empty());

    EXPECT_EQ(x[0], 'H');
    EXPECT_EQ(x.size(), 6);
    EXPECT_FALSE(x.empty());
}
