#include "meta17/Index.wrap.h"

using namespace meta17;

// unwrap
static_assert(to_value<Index<12>> == 12);

// wrap
static_assert(std::is_same_v<ToIndex<Const<3>>, Index<3>>);
