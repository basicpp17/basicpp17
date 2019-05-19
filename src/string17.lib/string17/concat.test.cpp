#include "concat.h"

#include "StringStore.byteCount.h"
#include "StringStore.ops.h"
#include "StringStore.ostream.h"
#include "StringView.h"
#include "storeLiteral.h"
#include "viewLiteral.h"

#include "meta17/Value.const.h"
#include "meta17/Value.ref.h"

#include <gtest/gtest.h>

using namespace string17;

using meta17::value;
using meta17::value_const;
using meta17::value_ref;

constexpr auto worldView = viewLiteral("World");

TEST(concat, example) {
    constexpr auto helloLambda = [] { return "Hello"; };
    static constexpr auto longStore = storeLiteral("long");

    constexpr auto r = concat(value<+helloLambda>, value_const<' '>, longStore, ' ', value_ref<worldView>);
    static_assert(r == storeLiteral("Hello long World"));
    EXPECT_EQ(r, storeLiteral("Hello long World"));
}
