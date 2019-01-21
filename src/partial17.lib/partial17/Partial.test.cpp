#include "Partial.h"

#include "Partial.make.h"
#include "Partial.trait.h"

#include <meta17/Const.ops.h> // index == index

#include <gtest/gtest.h>

using namespace partial17;

TEST(Partial, basic) {
    auto x = Partial<char, int, float>(); //
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

    ASSERT_EQ(created.get<0>(), 'a');
    ASSERT_EQ(created.get<2>(), 3.14f);

    auto copy = created;
    ASSERT_TRUE(copy.has<0>());
    ASSERT_FALSE(copy.has<1>());
    ASSERT_TRUE(copy.has<2>());

    ASSERT_EQ(copy.get<0>(), 'a');
    ASSERT_EQ(copy.get<2>(), 3.14f);
}
