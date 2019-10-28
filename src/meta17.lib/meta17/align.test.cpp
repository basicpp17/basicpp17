#include "align.h"

#include "Const.ops.h"
#include "IndexPack.h"

using namespace meta17;

static_assert(align_offset<3, 0> == 0);
static_assert(align_offset<3, 1> == 3);
static_assert(align_offset<3, 2> == 3);
static_assert(align_offset<3, 3> == 3);
static_assert(align_offset<3, 4> == 6);

// static_assert(alignOffset<3>(0) == 0); // expected to fail: not power of 2!

static_assert(alignOffset<4>(0) == 0);
static_assert(alignOffset<4>(1) == 4);
static_assert(alignOffset<4>(2) == 4);
static_assert(alignOffset<4>(3) == 4);
static_assert(alignOffset<4>(4) == 4);
static_assert(alignOffset<4>(5) == 8);
static_assert(alignOffset<4>(6) == 8);

static_assert(index_pack<0> == align_size_align_pack<0, IndexPack<1>, IndexPack<1>>);
static_assert(index_pack<0, 1> == align_size_align_pack<0, IndexPack<1, 1>, IndexPack<1, 1>>);
static_assert(index_pack<0, 2> == align_size_align_pack<0, IndexPack<1, 1>, IndexPack<1, 2>>);
static_assert(index_pack<0, 8, 12> == align_size_align_pack<0, IndexPack<2, 4, 4>, IndexPack<2, 8, 4>>);
