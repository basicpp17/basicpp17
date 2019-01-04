#include "OneOf.h"

#include "OneOf.make.h"

#include <gtest/gtest.h>

using namespace one_of17;

TEST(OneOf, basic) {
    auto x = MakeOneOf<TypePack<char, int, float>>{};

    auto s = x.visit([](auto v) { return sizeof(v); });
    ASSERT_EQ(s, 1);
}

TEST(OneOf, add) {
    auto x = OneOf<char, int, float>(3.14f);

    x.visit([](auto& v) { v += 3.2f; });

    x.visit([](auto v) {
        ASSERT_EQ(sizeof(v), sizeof(float));
        ASSERT_EQ(v, 3.14f + 3.2f);
    });
}

TEST(OneOf, emplace) {
    auto x = OneOf<char, int, float>(type<int>, 23.14f);

    x.visit([](auto v) {
        ASSERT_EQ(sizeof(v), sizeof(int));
        ASSERT_EQ(v, 23);
    });
}
