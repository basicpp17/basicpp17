#include "meta17/ConstPack.access.h"
#include "meta17/ConstPack.h"
#include "meta17/ConstPack.indexOf.h"
#include "meta17/ConstPack.ops.h"
#include "meta17/ConstPack.recurse.h"
#include "meta17/ConstPack.trait.h"
#include "meta17/ConstPack.wrap.h"

#include "meta17/Const.ops.h" // Const{} == Const{}

using namespace meta17;

static_assert(!is_const_pack<Const<1>>);
static_assert(is_const_pack<ConstPack<1, 2>>);

static_assert(const_pack<1, 2> == ConstPack<1, 1 + 1>{});
static_assert(to_const_pack<Const<1>, Const<2>> != const_pack<1, 2 + 3>);
static_assert(const_pack<1, 2> != ConstPack<1, 2, 3>{});

static_assert(toValue(const_pack<23>) == 23);

static_assert(constCount(const_pack<1, 2, 3>) == 3);
static_assert(constHead(const_pack<1, 2, 3>) == _const<1>);
static_assert(constTail(const_pack<1, 2, 3>) == const_pack<2, 3>);

static_assert(const_pack<1, 2> + const_pack<3> + _const<4> == const_pack<1, 2, 3, 4>);
static_assert(_const<1> + const_pack<2, 3> + const_pack<> == const_pack<1, 2, 3>);

static_assert(ConstAt<ConstPack<1, 2, 4>, Index<1>>{} == _const<2>);
static_assert(ConstLast<ConstPack<1, 2>>{} == _const<2>);

static_assert(count_const<1, ConstPack<1, 2, 3, 1>> == 2);
static_assert(contains_const<1, ConstPack<1, 2, 3>>);
static_assert(!contains_const<4, ConstPack<1, 2, 3>>);
