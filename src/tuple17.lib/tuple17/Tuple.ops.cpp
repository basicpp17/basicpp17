#include "Tuple.ops.h"

#include <gtest/gtest.h>

using namespace tuple17;

TEST(Tuple, ops) {
    using T = Tuple<int, double, char>;
    const T l1{23, 4.2, 'c'};
    const T l2{23, 4.2, 'b'};
    const T r1{23, 4.2, 'c'};
    const T r2{23, 4.2, 'd'};
    EXPECT_EQ(l1, r1);
    EXPECT_NE(l2, r2);
}
