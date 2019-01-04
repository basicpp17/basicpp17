#include "meta17/Const.typeOf.h"

#include "meta17/Type.ops.h" // type == type

using namespace meta17;

static_assert(type_of<Const<3>> == type<int>);
