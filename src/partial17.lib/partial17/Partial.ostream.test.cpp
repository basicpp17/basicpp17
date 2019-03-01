#include "Partial.ostream.h"

#include <gtest/gtest.h>
#include <sstream>

using namespace partial17;

TEST(Partial, ostream) {
    using P = Partial<int, double, char, short, bool>;
    const P p1{1, 'c', true}, p2{2.4, static_cast<short>(2)}; // see #workaround 1
    std::stringstream actual, expected;
    actual << p1 << " " << p2;
    expected << "<[1; c; 1]> <[2.4; 2]>";
    EXPECT_EQ(actual.str(), expected.str());
}
