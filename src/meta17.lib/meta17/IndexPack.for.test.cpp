#include "meta17/IndexPack.for.h"

#include "meta17/IndexPack.ops.h" // index_pack == index_pack

using namespace meta17;

static_assert(IndexPackFor<TypePack<char, int, float>>{} == index_pack<0, 1, 2>);

static_assert(IndexPackFor<ConstPack<1, 2, 5>>{} == index_pack<0, 1, 2>);
