#include "Variant.ostream.h"

#include <gtest/gtest.h>
#include <sstream>

using namespace variant17;

TEST(Variant, ostream) {
    using V = Variant<int, double, char, short, bool>;
    const V v1{1}, v2{2.6}, v3{'c'}, v4{static_cast<short>(2)}, v5{true};
    std::stringstream actual, expected;
    actual << v1 << " " << v2 << " " << v3 << " " << v4 << " " << v5;
    expected << "<1> <2.6> <c> <2> <1>";
    EXPECT_EQ(actual.str(), expected.str());
}
