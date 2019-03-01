#include "Partial.h"

#include "Partial.make.h"
#include "Partial.trait.h"

#include <meta17/Const.ops.h> // index == index

#include <gtest/gtest.h>

using namespace partial17;

using meta17::type;

TEST(Partial, construction) {
    using P = Partial<char, int, float>;
    auto p0 = P{};
    ASSERT_FALSE(p0.has<0>());
    ASSERT_FALSE(p0.has<1>());
    ASSERT_FALSE(p0.has<2>());
    //    EXPECT_EQ(p0.get<0>(), '\0');
    //    EXPECT_EQ(p0.get<1>(), 0);
    //    EXPECT_EQ(p0.get<2>(), 0);

    auto p1 = P{'c', 2.3f};
    auto p2 = p1; // copy constructor
    auto p3 = P{std::move(p2)}; // move construct
    // TODO CK: We need a better way to check for equality!
    //   EXPECT_EQ(p0, p2);
    ASSERT_TRUE(p1.has<0>());
    ASSERT_FALSE(p1.has<1>());
    ASSERT_TRUE(p1.has<2>());
    EXPECT_EQ(p1.count(), 2);

    ASSERT_TRUE(p3.has<0>());
    ASSERT_FALSE(p3.has<1>());
    ASSERT_TRUE(p3.has<2>());
    EXPECT_EQ(p3.count(), 2);

    EXPECT_EQ(p1.get<0>(), 'c');
    EXPECT_EQ(p1.get<2>(), 2.3f);
    EXPECT_EQ(p3.get<0>(), 'c');
    EXPECT_EQ(p3.get<2>(), 2.3f);
}

TEST(Partial, assignment) {
    using P = Partial<char, int, float>;
    auto p0 = P{'c', 2.3f};
    auto p1 = P{};
    p1 = p0; // copy operator
    auto p2 = P{};
    p2 = std::move(p1); // move operator
    // TODO CK: We need a better way to check for equality!
    //    EXPECT_EQ(p0, p2);
    ASSERT_TRUE(p0.has<0>());
    ASSERT_FALSE(p0.has<1>());
    ASSERT_TRUE(p0.has<2>());

    ASSERT_TRUE(p2.has<0>());
    ASSERT_FALSE(p2.has<1>());
    ASSERT_TRUE(p2.has<2>());

    EXPECT_EQ(p0.get<0>(), 'c');
    EXPECT_EQ(p0.get<2>(), 2.3f);
    EXPECT_EQ(p2.get<0>(), 'c');
    EXPECT_EQ(p2.get<2>(), 2.3f);
}

TEST(Partial, fromFactory) {
    const auto p = Partial<char, int, float>::fromFactory(
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
    ASSERT_TRUE(p.has<0>());
    ASSERT_FALSE(p.has<1>());
    ASSERT_TRUE(p.has<2>());

    EXPECT_EQ(p.get<0>(), 'a');
    EXPECT_EQ(p.get<2>(), 3.14f);
}

TEST(Partial, type) {
    auto p = Partial<char, int, float>{'\x23', 23};
    ASSERT_TRUE(p.has(type<char>));
    ASSERT_TRUE(p.has(0));
    EXPECT_EQ(0x23, p.get(type<char>));
    EXPECT_EQ(0x23, p.get(index<0>));
    ASSERT_TRUE(p.has(type<int>));
    ASSERT_TRUE(p.has(1));
    ASSERT_EQ(23, p.get(type<int>));
    EXPECT_EQ(23, p.get(index<1>));

    // TODO CK: Does prevent valid compilation - why? Primary error is thrown in unrelated test construction!
    //    auto m = Partial<int, int>{23, 32};
    //    // not allowed due to used TypePack
    //    // ASSERT_TRUE(m.has(type<int>));
    //    // ASSERT_EQ(23, m.get(type<int>));
    //    // TODO CK: API is confusing - has with size_t direct, get needs another abstraction?
    //    ASSERT_TRUE(m.has(0));
    //    EXPECT_EQ(23, m.get(index<0>));
    //    ASSERT_TRUE(m.has(1));
    //    EXPECT_EQ(32, m.get(index<1>));
}

TEST(Partial, merge) {
    // Disjunct merge
    using P = Partial<char, int, float>;
    auto p0 = P{'\x23'};
    auto p1 = P{2.3f};
    auto p2 = p0.merge(p1);
    ASSERT_TRUE(p2.has<0>());
    ASSERT_FALSE(p2.has<1>());
    ASSERT_TRUE(p2.has<2>());

    EXPECT_EQ(p2.get<0>(), '\x23');
    EXPECT_EQ(p2.get<2>(), 2.3f);

    // Overwrite merge
    auto p3 = P{2};
    auto p4 = P{4};
    auto p5 = p3.merge(p4);
    ASSERT_FALSE(p5.has<0>());
    ASSERT_TRUE(p5.has<1>());
    ASSERT_FALSE(p5.has<2>());

    EXPECT_EQ(p5.get<1>(), 4);

    auto p6 = p4.merge(p3);
    ASSERT_FALSE(p6.has<0>());
    ASSERT_TRUE(p6.has<1>());
    ASSERT_FALSE(p6.has<2>());

    EXPECT_EQ(p6.get<1>(), 2);
}
