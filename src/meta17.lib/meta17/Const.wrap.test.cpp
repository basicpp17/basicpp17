#include "meta17/Const.wrap.h"

#include <type_traits> // std::is_same_v

using namespace meta17;

// unwrap
static_assert(to_value<Const<23>> == 23);

// wrap
static_assert(std::is_same_v<ToConst<True>, Const<true>>);
