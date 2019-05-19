#include "Value.const.h"

using namespace meta17;

constexpr auto makeConst() { return value_const<42>; }

using Answer = decltype(makeConst());
static_assert(Answer::v == 42);
