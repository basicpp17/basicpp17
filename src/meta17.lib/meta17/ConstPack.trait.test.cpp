#include "meta17/ConstPack.trait.h"

using namespace meta17;

static_assert(is_const_pack<ConstPack<>>);
static_assert(is_const_pack<ConstPack<1, 2>>);
static_assert(!is_const_pack<int>);
