#include "meta17/IndexType.extract.h"

#include "meta17/Index.ops.h" // index == index
#include "meta17/Type.ops.h" // type == type

using namespace meta17;

static_assert(extract_index<IndexType<23, int>> == index<23>);
static_assert(extract_type<IndexType<23, int>> == type<int>);
