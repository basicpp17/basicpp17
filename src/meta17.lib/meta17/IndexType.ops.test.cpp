#include "meta17/IndexType.ops.h"

using namespace meta17;

static_assert(index_type<23, int> == IndexType<12 + 11, signed int>{});
static_assert(index_type<23, int> != index_type<22, int>);
static_assert(index_type<23, int> != index_type<23, char>);
