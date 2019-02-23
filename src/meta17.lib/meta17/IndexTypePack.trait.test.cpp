#include "meta17/IndexTypePack.trait.h"

using namespace meta17;

static_assert(is_index_type_pack<TypePack<>>);
static_assert(is_index_type_pack<TypePack<IndexType<23, int>>>);
static_assert(!is_index_type_pack<int>);
static_assert(!is_index_type_pack<TypePack<int>>);
static_assert(!is_index_type_pack<TypePack<IndexType<23, int>, int>>);
