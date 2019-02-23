#include "TypePack.wrap.h"

#include "TypePack.ops.h" // type_pack == type_pack

using namespace meta17;

static_assert(to_type_pack<int, Type<float>> == type_pack<int, float>);
static_assert(to_type_pack<TypePack<int, float>> == type_pack<int, float>);
