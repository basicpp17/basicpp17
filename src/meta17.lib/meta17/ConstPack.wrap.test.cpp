#include "meta17/ConstPack.wrap.h"

#include "meta17/ConstPack.ops.h"

using namespace meta17;

static_assert(to_value<ConstPack<23>> == 23);
static_assert(toValue(const_pack<42>) == 42);

static_assert(to_const_pack<ConstPack<1>, Const<2>> == const_pack<1, 2>);
