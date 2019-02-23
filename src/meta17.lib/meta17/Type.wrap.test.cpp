#include "meta17/Type.wrap.h"

#include "meta17/Type.ops.h" // type == type

using namespace meta17;

// unwrap
static_assert(std::is_same_v<UnwrapType<Type<int>>, UnwrapType<int>>);

// wrapping
static_assert(to_type<int> == to_type<Type<int>>);
