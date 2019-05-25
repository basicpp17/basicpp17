#include "storeView.h"
#include "viewLiteral.h"

#include <gtest/gtest.h>

using namespace string17;

TEST(storeView, basic) {
    constexpr auto v = viewLiteral("Hello");
    constexpr auto x = storeView<v.size()>(v);
    static_assert(x[0] == 'H');
    static_assert(x.size() == 5u);
    static_assert(!x.empty());

    EXPECT_EQ(x[0], 'H');
    EXPECT_EQ(x.size(), 5u);
    EXPECT_FALSE(x.empty());
}

TEST(storeView, extended) {
    constexpr auto v = viewLiteral("Hello");
    constexpr auto x = storeView<1 + v.size()>(v);
    static_assert(x[0] == 'H');
    static_assert(x.size() == 6u);
    static_assert(x[5] == '\0');
    static_assert(!x.empty());

    EXPECT_EQ(x[0], 'H');
    EXPECT_EQ(x.size(), 6u);
    EXPECT_FALSE(x.empty());
}
