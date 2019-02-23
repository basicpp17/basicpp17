#include "meta17/ConstPack.access.h"

using namespace meta17;

static_assert(ConstAt<ConstPack<1, 2, 4>, Index<1>>{} == _const<2>);
static_assert(const_at<ConstPack<1, 2, 3>, Index<2>> == _const<3>);

static_assert(ConstLast<ConstPack<1, 2>>{} == _const<2>);
static_assert(const_last<ConstPack<1>> == _const<1>);
