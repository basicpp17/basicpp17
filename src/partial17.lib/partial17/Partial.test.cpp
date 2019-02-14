#include "Partial.h"

#include "Partial.make.h"
#include "Partial.trait.h"

#include <meta17/Const.ops.h> // index == index

#include <gtest/gtest.h>

using namespace partial17;

TEST(Partial, basic) {
    auto x = Partial<char, int, float>{}; //
    auto y = x; // copy constructor
    x = y; // copy operator
    x = std::move(y); // move operator
    auto z = Partial<char, int, float>{std::move(x)}; // move construct
}

TEST(Partial, fromFactory) {
    const auto created = Partial<char, int, float>::fromFactory(
        [](size_t i) { return (0 == i % 2); },
        [](auto i) {
            if constexpr (i == index<0>) {
                return 'a';
            }
            if constexpr (i == index<1>) {
                return 23;
            }
            if constexpr (i == index<2>) {
                return 3.14f;
            }
        });
    ASSERT_TRUE(created.has<0>());
    ASSERT_FALSE(created.has<1>());
    ASSERT_TRUE(created.has<2>());

    EXPECT_EQ(created.get<0>(), 'a');
    EXPECT_EQ(created.get<2>(), 3.14f);

    auto copy = created;
    ASSERT_TRUE(copy.has<0>());
    ASSERT_FALSE(copy.has<1>());
    ASSERT_TRUE(copy.has<2>());

    EXPECT_EQ(copy.get<0>(), 'a');
    EXPECT_EQ(copy.get<2>(), 3.14f);
}

TEST(Partial, fromArgs) {
    const auto created = Partial<char, int, float>(3.14f, 'a'); //
    ASSERT_TRUE(created.has<0>());
    ASSERT_FALSE(created.has<1>());
    ASSERT_TRUE(created.has<2>());

    EXPECT_EQ(created.get<0>(), 'a');
    EXPECT_EQ(created.get<2>(), 3.14f);
}

TEST(Partial, byType) {

    auto x = Partial<char, int, float>{}; //
    if (x.has(meta17::Type<char>{})) {
        x.get(type<char>);
    }
}
