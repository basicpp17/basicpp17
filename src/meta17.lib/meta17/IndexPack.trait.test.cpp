#include "meta17/IndexPack.trait.h"

#include "meta17/Index.h"

using namespace meta17;

static_assert(is_index_pack<IndexPack<>>);
static_assert(is_index_pack<ConstPack<>>);

static_assert(!is_index_pack<int>);
static_assert(!is_index_pack<Index<0>>);
// static_assert(!is_index_pack<ConstPack<1, 2, 3>>); // warning: MSVC gets this wrong!
