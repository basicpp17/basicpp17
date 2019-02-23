#include "meta17/IndexType.trait.h"

using namespace meta17;

static_assert(!is_index_type<int>);
static_assert(is_index_type<IndexType<23, int>>);
