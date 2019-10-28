#include "Tuple.make.h"

#include "meta17/TypePack.h"

#include <gtest/gtest.h>

using namespace tuple17;
using meta17::Index;
using meta17::TypePack;

TEST(Tuple, make) {
    using T1 = MakeTuple<TypePack<int, double, char, int>>;
    static_assert(std::tuple_size<T1>::value == 4);

    using T2 = MakeTuple<TypePack<int, double, char, float>>;
    static_assert(std::tuple_size<T2>::value == 4);
}
