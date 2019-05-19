#include "StringView.h"
#include "viewCString.h"
#include "viewLiteral.h"

#include <string_view>

#include <gtest/gtest.h>

using namespace string17;

TEST(StringView, fromLiteral) {
    constexpr auto x = viewLiteral("Hello");
    static_assert(x[0] == 'H');
    static_assert(x.size() == 5);
    static_assert(!x.empty());

    EXPECT_EQ(x[0], 'H');
    // EXPECT_EQ(x.size(), 5); // MSVC seems to have a bug here
    EXPECT_FALSE(x.empty());

    auto y = viewLiteral("World");
    EXPECT_EQ(y[0], 'W');
    EXPECT_EQ(y.size(), 5);
    EXPECT_FALSE(y.empty());

    static auto z = x;
    EXPECT_EQ(z[0], 'H');
    // EXPECT_EQ(z.size(), 5); // MSVC seems to have a bug here
    EXPECT_FALSE(z.empty());
}

TEST(StringView, fromCString) {
    static constexpr auto* cstr = "Hello";
    constexpr auto x = viewCString(cstr);
    static_assert(x[0] == 'H');
    static_assert(x.size() == 5);
    static_assert(!x.empty());

    EXPECT_EQ(x[0], 'H');
    // EXPECT_EQ(x.size(), 5); // MSVC seems to have a bug here
    EXPECT_FALSE(x.empty());

    auto* ystr = "World";
    auto y = viewCString(ystr);
    EXPECT_EQ(y[0], 'W');
    EXPECT_EQ(y.size(), 5);
    EXPECT_FALSE(y.empty());
}
