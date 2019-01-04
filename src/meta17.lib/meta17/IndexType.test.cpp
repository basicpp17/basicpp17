#include "meta17/IndexType.extract.h"
#include "meta17/IndexType.h"
#include "meta17/IndexType.ops.h"
#include "meta17/IndexType.trait.h"

#include "meta17/Index.ops.h"
#include "meta17/Type.ops.h"

using namespace meta17;

static_assert(!is_index_type<int>);
static_assert(is_index_type<IndexType<23, int>>);

static_assert(extract_index<IndexType<23, int>> == index<23>);
static_assert(extract_type<IndexType<23, int>> == type<int>);

static_assert(index_type<23, int> == IndexType<12 + 11, signed int>{});
static_assert(index_type<23, int> != index_type<22, int>);
static_assert(index_type<23, int> != index_type<23, char>);
