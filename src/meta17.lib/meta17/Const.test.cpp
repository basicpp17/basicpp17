#include "meta17/Const.h"
#include "meta17/Const.ops.h"
#include "meta17/Const.trait.h"
#include "meta17/Const.wrap.h"

using namespace meta17;

// trait
static_assert(is_const<Const<3>>);
static_assert(!is_const<int>);

// unwrap
static_assert(to_value<Const<23>> == 23);

// wrap
static_assert(std::is_same_v<ToConst<True>, Const<true>>);

// equality & ordering
static_assert(Const<23>{} == 23);
static_assert(Const<0>{} != 3);
static_assert(Const<1>{} < Const<2>{});
static_assert(Const<3>{} > Const<2>{});

static_assert(Const<1>{} == Const<true>{});
static_assert(Const<1>{} == 1); // Const<1> == Const<true>
static_assert(1 > Const<0>{});

// calculations
static_assert(Const<1>{} + Const<5>{} == Const<6>{});
static_assert(Const<1>{} - Const<5>{} == Const<-4>{});

static_assert(Const<2>{} * Const<5>{} == Const<10>{});
static_assert(Const<false>{} * Const<5>{} == Const<0>{}); // bool works nice
static_assert(Const<5>{} * Const<true>{} == Const<5>{}); // bool works nice

// static_assert(Const<10>{} / Const<0>{} || true); // wont compile
static_assert(Const<10>{} / Const<1>{} == Const<10>{});
static_assert(Const<10>{} / Const<2>{} == Const<5>{});
static_assert(Const<10>{} % Const<5>{} == Const<0>{});
