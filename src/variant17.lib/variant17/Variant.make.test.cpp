#include "Variant.make.h"

#include <gtest/gtest.h>

using namespace variant17;

TEST(Variant, make) {
    using V = MakeVariant<TypePack<char, int, float>>;
    const V v{};
    auto s = v.visit([](auto v) { return sizeof(v); });
    EXPECT_EQ(s, size_t{1});
}
