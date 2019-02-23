#include "meta17/Const.ops.h"

using namespace meta17;

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
