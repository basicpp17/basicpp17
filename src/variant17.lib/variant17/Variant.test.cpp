#include "Variant.h"

#include "Variant.make.h"

#include <gtest/gtest.h>

using namespace variant17;

TEST(Variant, basic) {
    auto x = MakeVariant<TypePack<char, int, float>>{};

    auto s = x.visit([](auto v) { return sizeof(v); });
    ASSERT_EQ(s, size_t{1});
}

TEST(Variant, add) {
    auto x = Variant<char, int, float>(3.14f);

    x.visit([](auto& v) { v += 3.2f; });

    x.visit([](auto v) {
        ASSERT_EQ(sizeof(v), sizeof(float));
        ASSERT_EQ(v, 3.14f + 3.2f);
    });
}

TEST(Variant, emplace) {
    auto x = Variant<char, int, float>(type<int>, 23.14f);

    x.visit([](auto v) {
        ASSERT_EQ(sizeof(v), sizeof(int));
        ASSERT_EQ(v, 23);
    });
}
