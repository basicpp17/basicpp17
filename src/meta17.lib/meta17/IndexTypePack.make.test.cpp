#include "meta17/IndexTypePack.make.h"

#include "meta17/TypePack.ops.h" // type_pack == type_pack

using namespace meta17;

static_assert(make_index_type_pack<TypePack<>> == type_pack<>);
static_assert(makeIndexTypePack<char, int>() == type_pack<IndexType<0, char>, IndexType<1, int>>);
static_assert(makeIndexTypePack<IndexType<23, char>, int>() == type_pack<IndexType<23, char>, IndexType<24, int>>);
