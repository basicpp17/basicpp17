#include "Variant.h"

#include "Variant.ops.h"

#include "meta17/Index.h"
#include "meta17/Type.ops.h"

#include <gtest/gtest.h>

using namespace variant17;

TEST(Variant, construction) {
    using meta17::index;
    // Standard
    using V = Variant<char, int, double>;
    auto v0 = V{};
    auto v1 = v0; // copy
    auto v2 = std::move(v1); // move copy
    EXPECT_EQ(v0, v2);

    // Inplace creation with type
    auto v3 = Variant<char, int, float>(type<int>, 23.14f);
    v3.visit([](auto value) {
        EXPECT_EQ(sizeof(value), sizeof(int));
        EXPECT_EQ(value, 23);
    });

    // Inplace creation with index
    auto v4 = Variant<char, int, float>(index<1>, 23.14f);
    v4.visit([](auto value) {
        ASSERT_EQ(sizeof(value), sizeof(int));
        ASSERT_EQ(value, 23);
    });

    // Type without default
    struct S {
        S() = delete;
        S(int) {}
    };
    auto v5 = Variant<S>(type<S>, 2);
    v5.visit([](auto value) { EXPECT_EQ(sizeof(value), sizeof(S)); });
}

TEST(Variant, emplace) {
    using meta17::index;
    using V = Variant<char, int, float>;

    // Inplace change of type with type
    auto v0 = V{};
    v0.emplace(type<int>, 23.14f);
    v0.visit([](auto value) {
        EXPECT_EQ(sizeof(value), sizeof(int));
        EXPECT_EQ(value, 23);
    });

    // Inplace change of type with index
    auto v1 = V{};
    v1.emplace(index<1>, 23.14f);
    v1.visit([](auto value) {
        ASSERT_EQ(sizeof(value), sizeof(int));
        ASSERT_EQ(value, 23);
    });
}

TEST(Variant, which) {
    using V = Variant<char, int, float>;
    V v{};

    ASSERT_EQ(v.which(), type<char>);
    ASSERT_NE(v.which(), type<int>);
    ASSERT_NE(v.which(), type<float>);

    v = 3.2f;

    ASSERT_NE(v.which(), type<char>);
    ASSERT_NE(v.which(), type<int>);
    ASSERT_EQ(v.which(), type<float>);

    static_assert(V::whichOf<char>() == type<char>);
    // Should not compile due to double is not part of V
    // static_assert(V::whichOf<double>() == type<double>);
}

TEST(Variant, type) {
    using V = Variant<char, int, float>;
    static_assert(V::type_at<0> == type<char>);
    static_assert(V::type_at<1> == type<int>);
    static_assert(V::type_at<2> == type<float>);
    // Should not compile due to double is not part of V
    static_assert(V::type_at<2> != type<double>);
    // Should not compile since V has only 3 options
    // static_assert(V::type_at<3> == type<float>);
}

TEST(Variant, visit) {
    auto v = Variant<char, int, float>{};

    auto size0 = v.visit([](auto value) { return sizeof(value); });
    EXPECT_EQ(size0, sizeof(char));

    v = 3.2f;

    auto size1 = v.visit([](auto value) { return sizeof(value); });
    EXPECT_EQ(size1, sizeof(float));
}

TEST(Variant, manip) {
    using V = Variant<char, int, float>;
    V v1(3.14f), v2('c');

    v1.visit([](auto& value) { value += 3.2f; });
    v1.visit([](int& value) { value -= 1; }, [](char&) {}, [](float& value) { value += 1; });

    v1.visit([](auto value) {
        EXPECT_EQ(sizeof(value), sizeof(float));
        EXPECT_EQ(value, 3.14f + 3.2f + 1);
    });

    v2.visit([](auto& value) { value += 3.2f; });
    v2.visit([](int& value) { value -= 1; }, [](char&) {}, [](float& value) { value += 1; });
    v2.visit([](auto value) {
        EXPECT_EQ(sizeof(value), sizeof(char));
        EXPECT_EQ(value, 'f');
    });
}

TEST(Variant, overloaded) {
    auto v = Variant<char, int, float>{};

    auto charVisitor = [](char) { return 1; };
    auto intVisitor = [](int) { return 2; };
    auto floatVisitor = [](float) { return 3; };

    EXPECT_EQ(1, v.visit(charVisitor, intVisitor, floatVisitor));
    v = 1;
    EXPECT_EQ(2, v.visit(charVisitor, intVisitor, floatVisitor));
    v = 3.2f;
    EXPECT_EQ(3, v.visit(charVisitor, intVisitor, floatVisitor));
}
