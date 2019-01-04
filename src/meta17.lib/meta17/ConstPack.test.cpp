#include "meta17/ConstPack.access.h"
#include "meta17/ConstPack.h"
#include "meta17/ConstPack.ops.h"
#include "meta17/ConstPack.recurse.h"
#include "meta17/ConstPack.trait.h"
#include "meta17/ConstPack.wrap.h"

#include "meta17/Const.ops.h" // Const{} == Const{}

using namespace meta17;

static_assert(!is_const_pack<Const<1>>);
static_assert(is_const_pack<ConstPack<1, 2>>);

static_assert(const_pack<1, 2> == ConstPack<1, 1 + 1>{});
static_assert(to_const_pack<Const<1>, Const<2>> != ConstPack<1, 2 + 3>{});
static_assert(ConstPack<1, 2>{} != ConstPack<1, 2, 3>{});

static_assert(toValue(ConstPack<23>{}) == 23);

static_assert(constCount(ConstPack<1, 2, 3>{}) == 3);
static_assert(constHead(ConstPack<1, 2, 3>{}) == Const<1>{});
static_assert(constTail(ConstPack<1, 2, 3>{}) == ConstPack<2, 3>{});

static_assert(ConstPack<1, 2>{} + ConstPack<3>{} + Const<4>{} == ConstPack<1, 2, 3, 4>{});
static_assert(Const<1>{} + ConstPack<2, 3>{} + ConstPack<>{} == ConstPack<1, 2, 3>{});

static_assert(ConstAt<ConstPack<1, 2, 4>, Index<1>>{} == Const<2>{});
static_assert(ConstLast<ConstPack<1, 2>>{} == Const<2>{});
