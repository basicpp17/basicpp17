#include "StringStore.foreach.h"

#include <gtest/gtest.h>

using namespace string17;

TEST(StringStoreForEach, basic) {
    constexpr auto x = StringStore{"Hello"};
    constexpr auto l = [&] {
        auto s = 0;
        for (auto c : x) s += c;
        return s;
    }();
    static_assert(l == 500);

    EXPECT_EQ(l, 500);
}
