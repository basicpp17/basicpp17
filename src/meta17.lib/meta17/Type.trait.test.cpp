#include "meta17/Type.trait.h"

using namespace meta17;

static_assert(is_type<Type<int>>);
static_assert(!is_type<int>);
