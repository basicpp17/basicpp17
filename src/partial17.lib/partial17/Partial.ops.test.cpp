#include "Partial.ops.h"

#include <gtest/gtest.h>

using namespace partial17;

TEST(Partial, ops) {
    //    using P1 = Partial<char, int, float, bool>;
    //    using P2 = Partial<bool, float, int, char>;

    //    auto p1 = P1{'c', 2.3f};
    //    auto p2 = P2{'c', 2.3f};
    //    EXPECT_EQ(p1, p2);

    using P = Partial<char, int, float, bool>;
    const P p1{3.2f};
    const P p2{3.2f};
    EXPECT_EQ(p1, p2);

    const P p3{3.1f};
    const P p4{3.3f};
    EXPECT_NE(p3, p4);

    const P p5{99};
    const P p6{'c'};
    EXPECT_NE(p5, p6);

    const P p7{'c', 3.2f};
    const P p8{3.2f};
    EXPECT_NE(p7, p8);
}
