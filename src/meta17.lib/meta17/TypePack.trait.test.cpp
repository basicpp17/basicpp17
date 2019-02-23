#include "TypePack.trait.h"

using namespace meta17;

static_assert(is_type_pack<TypePack<int>>);
static_assert(is_type_pack<TypePack<>>);
static_assert(!is_type_pack<int>);
