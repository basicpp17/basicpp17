#include "Value.h"

using namespace meta17;

constexpr auto constAnswer() { return 42; }

using Answer = Value<constAnswer>;
static_assert(Answer::v == 42);

constexpr auto answer() { return value<constAnswer>; }
static_assert(answer().v == 42);
