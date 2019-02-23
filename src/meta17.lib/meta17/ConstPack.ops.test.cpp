#include "ConstPack.ops.h"

using namespace meta17;

static_assert(const_pack<1, 2> == ConstPack<1, 1 + 1>{});
static_assert(const_pack<1, 2> != ConstPack<1, 2, 3>{});

static_assert(const_pack<1, 2> + const_pack<3> + _const<4> == const_pack<1, 2, 3, 4>);
static_assert(_const<1> + const_pack<2, 3> + const_pack<> == const_pack<1, 2, 3>);
