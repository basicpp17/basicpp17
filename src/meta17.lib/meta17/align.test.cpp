#include <meta17/align.h>

#include "Const.ops.h"
#include "IndexPack.h"

using namespace meta17;

static_assert(alignOffset<0, 3>() == _const<0>);
static_assert(alignOffset<1, 3>() == _const<3>);
static_assert(alignOffset<2, 3>() == _const<3>);
static_assert(alignOffset<3, 3>() == _const<3>);
static_assert(alignOffset<4, 3>() == _const<6>);

static_assert(index_pack<0> == alignSizeAlignPack<0>(index_pack<1>, index_pack<1>));
static_assert(index_pack<0, 1> == alignSizeAlignPack<0>(index_pack<1, 1>, index_pack<1, 1>));
static_assert(index_pack<0, 2> == alignSizeAlignPack<0>(index_pack<1, 1>, index_pack<1, 2>));
static_assert(index_pack<0, 8, 12> == alignSizeAlignPack<0>(index_pack<2, 4, 4>, index_pack<2, 8, 4>));
