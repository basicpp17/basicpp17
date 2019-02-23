#include "meta17/Index.ops.h"

using namespace meta17;

// equality
static_assert(index<3> == 3);

// add
static_assert(index<3> + index<1> == 4);
static_assert(index<3> - index<1> == 2);
static_assert(index<3> - index<5> == -2);
