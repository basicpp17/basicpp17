#include "meta17/ConstPack.indexOf.h"

using namespace meta17;

static_assert(count_const<1, ConstPack<1, 2, 3, 1>> == 2);
static_assert(count_const<-1, ConstPack<1, 2, 3, 1>> == 0);

static_assert(contains_const<1, ConstPack<1, 2, 3>>);
static_assert(!contains_const<4, ConstPack<1, 2, 3>>);

static_assert(index_const<3, ConstPack<1, 2, 3>> == 2);
static_assert(index_const<-1, ConstPack<1, 2, 3>> == 3);
