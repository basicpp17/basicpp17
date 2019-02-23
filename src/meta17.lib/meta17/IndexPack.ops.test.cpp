#include "meta17/IndexPack.ops.h"

#include "meta17/Index.h"

using namespace meta17;

static_assert(index_pack<1, 2> == ConstPack<1, 1 + 1>{});
static_assert(index_pack<1, 2> != ConstPack<1, 2, 3>{});

static_assert(index_pack<1, 2> + index_pack<3> + index<4> == index_pack<1, 2, 3, 4>);
static_assert(index<1> + index_pack<2, 3> + index_pack<> == index_pack<1, 2, 3>);
