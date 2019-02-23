#include "meta17/IndexTypePack.extract.h"

#include "meta17/IndexPack.ops.h" // index_pack == index_pack
#include "meta17/TypePack.ops.h" // type_pack == type_pack

using namespace meta17;

static_assert(extract_index_pack<TypePack<IndexType<23, int>>> == index_pack<23>);
static_assert(extract_type_pack<TypePack<IndexType<23, int>>> == type_pack<int>);
