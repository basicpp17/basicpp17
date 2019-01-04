#include "meta17/Bool.h"
#include "meta17/Bool.wrap.h"

using namespace meta17;

// use in conditions
static_assert(True{}, "easy condition with True");
static_assert(!False{}, "easy condition with False");

// unwrap
static_assert(to_value<True>, "unwrapped True");
static_assert(!to_value<False>, "unwrapped False");
