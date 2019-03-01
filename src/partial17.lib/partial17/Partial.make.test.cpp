#include "Partial.h"

#include "Partial.make.h"
#include "Partial.trait.h"

#include <meta17/Const.ops.h>
#include <meta17/Type.ops.h>

#include <gtest/gtest.h>

using namespace partial17;

using meta17::type;

TEST(Partial, make) {
    using PM = MakePartial<TypePack<char, int, float>>;
    using PC = Partial<char, int, float>;

    static_assert(type<PM> == type<PC>);
}
