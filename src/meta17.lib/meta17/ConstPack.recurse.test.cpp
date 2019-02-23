#include "meta17/ConstPack.recurse.h"

#include "meta17/Const.ops.h" // Const{} == Const{}

using namespace meta17;

static_assert(const_count<ConstPack<1, 2, 3>> == 3);
static_assert(const_head<ConstPack<1, 2, 3>> == _const<1>);
static_assert(constHead(const_tail<ConstPack<1, 2, 3>>) == _const<2>);
static_assert(constHead(constTail(constTail(const_pack<1, 2, 3>))) == _const<3>);
