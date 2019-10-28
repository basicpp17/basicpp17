#include "meta17/Const.wrap.h"

#include "meta17/same.h"

using namespace meta17;

// unwrap
static_assert(to_value<Const<23>> == 23);

// wrap
static_assert(same<ToConst<True>, Const<true>>);
