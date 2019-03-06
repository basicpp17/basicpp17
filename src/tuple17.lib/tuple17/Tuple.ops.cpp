#include "Tuple.ops.h"

#include <gtest/gtest.h>

using namespace tuple17;

TEST(Tuple, ops) {
    // Should not compile due to different types
    //    using T1 = Tuple<int, double, char>;
    //    using T2 = Tuple<char, double, int>;
    //    const T1 t1{23, 4.2, 'c'};
    //    const T2 t2{'c', 4.2, 23};
    //    EXPECT_NE(t1, t2);

    using T = Tuple<int, double, char>;
    const T l1{23, 4.2, 'c'};
    const T r1{23, 4.2, 'c'};
    EXPECT_EQ(l1, r1);

    const T l2{23, 4.2, 'b'};
    const T r2{23, 4.2, 'd'};
    EXPECT_NE(l2, r2);
}
