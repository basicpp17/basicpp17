#include "Variant.ops.h"

#include <gtest/gtest.h>

using namespace variant17;

TEST(Variant, ops) {
    using V = Variant<char, int, float, bool>;
    const V v1{3.2f};
    const V v2{3.2f};
    EXPECT_EQ(v1, v2);

    const V v3{3.1f};
    const V v4{3.3f};
    EXPECT_NE(v3, v4);

    const V v5{99};
    const V v6{'c'};
    EXPECT_NE(v5, v6);

    const V v7{false};
    const V v8{0};
    EXPECT_NE(v7, v8);
}
