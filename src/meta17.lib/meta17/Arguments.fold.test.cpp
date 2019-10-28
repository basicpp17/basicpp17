#include "meta17/Arguments.fold.h"

using namespace meta17;

static_assert(accumulateArguments(1, 2, 3) == 6);

static_assert(accumulate_instances<int, int, int> == 0);

static_assert(true == allArguments(true, 1, 2));
static_assert(false == allArguments(false, 1, 2));

static_assert(true == anyArgument(false, 0, true));
static_assert(false == anyArgument(false, 0));
