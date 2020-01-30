#include "Strong.opaque.h"

#include <gtest/gtest.h>

namespace testing {

STRONG_OPAQUE(HelloTest, int, struct HelloTag);

} // namespace testing

STRONG_OPAQUE(HelloGlobal, int, struct HelloTag);

TEST(Strong, opaque) {
    constexpr auto ht = testing::HelloTest{15};
    static_assert(ht.v == 15);

    constexpr auto hg = HelloGlobal{23};
    static_assert(hg.v == 23);
}
