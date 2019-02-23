#include "meta17/Index.trait.h"

using namespace meta17;

static_assert(is_index<Index<3>>);
static_assert(is_index<Const<size_t{3}>>);

static_assert(!is_index<int>);
// static_assert(!is_index<Const<(-3)>>); // warning: MSVC gets this wrong!
static_assert(!is_index<True>);
