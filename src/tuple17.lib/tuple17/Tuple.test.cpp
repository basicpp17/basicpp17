#include "Tuple.h"

#include "Tuple.make.h"
#include "Tuple.ops.h"

#include <meta17/Type.ops.h>

#include <gtest/gtest.h>

using namespace tuple17;
using meta17::Index;

TEST(Tuple, basic) {
    using X = Tuple<char, int, double>;
    auto x = X{};

    static_assert(sizeof(x) == 16);
    static_assert(X::offset_of<double> == 8);
    static_assert(X::offset_at<1> == 4);
    static_assert(X::type_at<1> == type<int>);

    x.at(index<1>) = 23;
    x.of<double>() = 4.2;
    ASSERT_EQ((x.of<int>()), 23);
    ASSERT_EQ((x.at<2>()), 4.2);

    auto y = x; // copy
    auto z = std::move(y); // move copy

    ASSERT_EQ(x, z);

    using G = MakeTuple<TypePack<int, double, char, float>>; // other order / bigger
    auto g = G(x);

    ASSERT_EQ((g.of<double>()), 4.2);
    ASSERT_EQ((g.of<int>()), 23);
    ASSERT_EQ((g.of<float>()), 0);
}
