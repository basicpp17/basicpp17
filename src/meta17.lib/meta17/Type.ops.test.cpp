#include "meta17/Type.ops.h"

using namespace meta17;

// equality
static_assert(type<int> == type<signed int>);
static_assert(type<float> != Type<double>{});
