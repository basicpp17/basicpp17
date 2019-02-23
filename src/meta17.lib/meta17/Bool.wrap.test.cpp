#include "meta17/Bool.wrap.h"

using namespace meta17;

// unwrap
static_assert(to_value<True>, "unwrapped True");
static_assert(!to_value<False>, "unwrapped False");
