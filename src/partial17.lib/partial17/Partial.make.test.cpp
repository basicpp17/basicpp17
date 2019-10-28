#include "Partial.h"

#include "Partial.make.h"
#include "Partial.trait.h"

#include "meta17/Const.ops.h"
#include "meta17/TypePack.h"
#include "meta17/same.h"

#include <gtest/gtest.h>

using namespace partial17;

using meta17::same;

TEST(Partial, make) {
    using PM = MakePartial<TypePack<char, int, float>>;
    using PC = Partial<char, int, float>;

    static_assert(same<PM, PC>);
}
