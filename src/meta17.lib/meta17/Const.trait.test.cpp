#include "meta17/Const.trait.h"

using namespace meta17;

static_assert(is_const<Const<3>>);
static_assert(!is_const<int>);
