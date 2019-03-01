#include "Partial.h"

#include "Partial.make.h"
#include "Partial.ops.h"
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
    // TODO CK: Should this be possible? - crashes, would suggest a graceful value for production
    //    EXPECT_EQ(p0.get<0>(), '\0');
    //    EXPECT_EQ(p0.get<1>(), 0);
    //    EXPECT_EQ(p0.get<2>(), 0);

    auto p1 = P{'c', 2.3f};
    auto p2 = p1; // copy constructor
    auto p3 = P{std::move(p2)}; // move construct

    EXPECT_EQ(p1.get<0>(), 'c');
    EXPECT_EQ(p1.get<2>(), 2.3f);
    EXPECT_EQ(p1.countInitialized(), 2ul);
    EXPECT_EQ(p1.countAll(), 3ul);
    // TODO CK: Consider alignment - does this need to consider the size of the bitset
    EXPECT_EQ(p1.size(), sizeof(int) + sizeof(float));
    EXPECT_EQ(p3.countInitialized(), 2ul);
    EXPECT_EQ(p3.countAll(), 3ul);
    EXPECT_EQ(p1.size(), sizeof(int) + sizeof(float));
    EXPECT_EQ(p1, p3);
}

TEST(Partial, assignment) {
    using P = Partial<char, int, float>;
    auto p0 = P{'c', 2.3f};
    auto p1 = P{};
    p1 = p0; // copy operator
    auto p2 = P{};
    p2 = std::move(p1); // move operator

    EXPECT_EQ(p0.get<0>(), 'c');
    EXPECT_EQ(p0.get<2>(), 2.3f);
    EXPECT_EQ(p0, p2);
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

    // TODO CK: Does prevent valid compilation? Microsoft Visual C++ BUG?
    // auto m = Partial<int, int>{23, 32};
    // not allowed due to used TypePack
    // ASSERT_TRUE(m.has(type<int>));
    // ASSERT_EQ(23, m.get(type<int>));
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

TEST(Partial, visitAll) {
    using P = Partial<char, int, float>;
    auto p = P{'\x23'};

    ASSERT_EQ(p.countInitialized(), 1ul);
    ASSERT_EQ(p.countAll(), 3ul);

    size_t count = 0;
    p.visitAll([&](auto i, auto t) {
        ++count;
        if (i == 0) {
            EXPECT_TRUE(p.has(i));
            EXPECT_EQ(t, type<char>);
        }
        else {
            EXPECT_FALSE(p.has(i));
            EXPECT_NE(t, type<char>);
        }
    });
    EXPECT_EQ(count, p.countAll());
}

TEST(Partial, visitInitialized) {
    using P = Partial<char, int, float>;
    auto p = P{'\x23', 2.3f};

    ASSERT_EQ(p.countInitialized(), 2ul);
    ASSERT_EQ(p.countAll(), 3ul);

    size_t count = 0;
    p.visitInitialized([&](auto v) {
        ++count;
        EXPECT_TRUE(type<decltype(v)> == type<char> || type<decltype(v)> == type<float>);
    });
    EXPECT_EQ(count, p.countInitialized());
}
