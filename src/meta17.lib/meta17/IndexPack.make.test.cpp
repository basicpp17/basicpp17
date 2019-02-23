#include "meta17/IndexPack.make.h"

#include "meta17/IndexPack.ops.h" // index_pack == index_pack

using namespace meta17;

static_assert(make_index_pack<3> == index_pack<0, 1, 2>);
static_assert(make_index_pack<0> == index_pack<>);
