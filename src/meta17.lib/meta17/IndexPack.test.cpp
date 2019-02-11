#include "meta17/IndexPack.h"
#include "meta17/IndexPack.make.h"
#include "meta17/IndexPack.ops.h"
#include "meta17/IndexPack.trait.h"
#include "meta17/IndexPack.wrap.h"

#include "meta17/Const.ops.h"
#include "meta17/ConstPack.access.h"

using namespace meta17;

static_assert(make_index_pack<3> == IndexPack<0, 1, 2>{});

static_assert(ConstAt<IndexPack<1, 2, 4>, Index<1>>{} == index<2>);
static_assert(ConstLast<IndexPack<1, 2>>{} == index<2>);
