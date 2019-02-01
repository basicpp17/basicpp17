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
static_assert(_const<23> == 23);
static_assert(Const<0>{} != 3);
static_assert(_const<1> < Const<2>{});
static_assert(_const<3>> _const<2>);

static_assert(_const<1> == Const<true>{});
static_assert(_const<1> == 1); // Const<1> == Const<true>
static_assert(1 > _const<0>);

// calculations
static_assert(_const<1> + _const<5> == _const<6>);
static_assert(_const<1> - _const<5> == _const<-4>);

static_assert(_const<2> * _const<5> == _const<10>);
static_assert(_const<false> * _const<5> == _const<0>); // bool works nice
static_assert(_const<5> * _const<true> == _const<5>); // bool works nice

// static_assert(_const<10> / _const<0> || true); // wont compile
static_assert(_const<10> / _const<1> == _const<10>);
static_assert(_const<10> / _const<2> == _const<5>);
static_assert(_const<10> % _const<5> == _const<0>);
