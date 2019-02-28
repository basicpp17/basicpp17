#include "Tuple.ostream.h"

#include <gtest/gtest.h>
#include <sstream>

using namespace tuple17;

TEST(Tuple, ostream) {
    using T = Tuple<int, double, char, short, bool>;
    const T t{2, 4.2, 'c', 3, false};
    std::stringstream actual, expected;
    actual << t;
    expected << "[2; 4.2; c; 3; 0]";
    EXPECT_EQ(actual.str(), expected.str());
}

TEST(Tuple, ostreamTODO_1) {
    // TODO CK: Does not work for multiple use - ostream should work using indices
    /*
     * using T = Tuple<int, double, char, int>;
     * const T t{2, 4.2, 'c', 3};
     * std::stringstream actual, expected;
     * actual << t;
     * expected << "[2; 4.2; c; 3]";
     * EXPECT_EQ(actual.str(), expected.str());
     */
}
