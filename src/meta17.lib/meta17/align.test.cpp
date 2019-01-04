#include <meta17/align.h>

#include "Const.ops.h"
#include "IndexPack.h"

using namespace meta17;

static_assert(alignOffset<0, 3>() == Const<0>{});
static_assert(alignOffset<1, 3>() == Const<3>{});
static_assert(alignOffset<2, 3>() == Const<3>{});
static_assert(alignOffset<3, 3>() == Const<3>{});
static_assert(alignOffset<4, 3>() == Const<6>{});

static_assert(IndexPack<0>{} == alignSizeAlignPack<0>(IndexPack<1>{}, IndexPack<1>{}));
static_assert(IndexPack<0, 1>{} == alignSizeAlignPack<0>(IndexPack<1, 1>{}, IndexPack<1, 1>{}));
static_assert(IndexPack<0, 2>{} == alignSizeAlignPack<0>(IndexPack<1, 1>{}, IndexPack<1, 2>{}));
static_assert(IndexPack<0, 8, 12>{} == alignSizeAlignPack<0>(IndexPack<2, 4, 4>{}, IndexPack<2, 8, 4>{}));
