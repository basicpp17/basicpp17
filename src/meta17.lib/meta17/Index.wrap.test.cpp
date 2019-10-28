#include "meta17/Index.wrap.h"

#include "meta17/same.h"

using namespace meta17;

// unwrap
static_assert(to_value<Index<12>> == 12);

// wrap
static_assert(same<ToIndex<Const<3>>, Index<3>>);
