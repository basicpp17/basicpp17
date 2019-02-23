#include "TypePack.recurse.h"

#include "TypePack.ops.h" // type_pack == type_pack

using namespace meta17;

static_assert(typeCount<char, int, float>() == 3);
static_assert(type_count<TypePack<char, int, float>> == 3);

static_assert(type_head<TypePack<char, int, float>> == type<char>);

static_assert(type_tail<TypePack<char, int, float>> == type_pack<int, float>);
