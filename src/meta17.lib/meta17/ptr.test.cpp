#include "ptr.h"
#include "same.h"

using namespace meta17;

static_assert(same<decltype(nullptr_to<int>), int* const>);
static_assert(nullptr_to<int> == nullptr);
