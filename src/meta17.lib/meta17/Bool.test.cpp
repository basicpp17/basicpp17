#include "meta17/Bool.h"

using namespace meta17;

// use in conditions
static_assert(True{}, "easy condition with True");
static_assert(!False{}, "easy condition with False");
