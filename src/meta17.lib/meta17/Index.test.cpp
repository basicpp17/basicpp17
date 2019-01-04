#include "meta17/Index.h"
#include "meta17/Index.ops.h"
#include "meta17/Index.trait.h"
#include "meta17/Index.wrap.h"

#include "meta17/Bool.wrap.h"

using namespace meta17;

// trait
static_assert(is_index<Index<3>>);
static_assert(!is_index<int>);

// unwrap
static_assert(to_value<Index<12>> == 12);

// wrap
static_assert(std::is_same_v<ToIndex<Const<3>>, Index<3>>);

// equality
static_assert(Index<3>{} == 3);
