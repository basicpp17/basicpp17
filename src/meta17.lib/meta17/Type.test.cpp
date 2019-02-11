#include "meta17/Type.h"
#include "meta17/Type.ops.h"
#include "meta17/Type.trait.h"
#include "meta17/Type.wrap.h"

using namespace meta17;

// trait
static_assert(is_type<Type<int>>);
static_assert(!is_type<int>);

// unwrap
static_assert(std::is_same_v<UnwrapType<Type<int>>, UnwrapType<int>>);

// equality
static_assert(type<int> == type<signed int>);
static_assert(type<float> != Type<double>{});

// wrapping
static_assert(to_type<int> == to_type<Type<int>>);
