#include "meta17/IndexPack.wrap.h"

#include "meta17/Index.wrap.h"
#include "meta17/IndexPack.ops.h" // index_pack == index_pack

using namespace meta17;

static_assert(to_value<IndexPack<23>> == 23);

static_assert(to_index_pack<Index<1>, IndexPack<2>> == index_pack<1, 2>);
