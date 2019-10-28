#include "TemplateOfValues.recurse.h"

#include "Const.ops.h" // _const == _const
#include "ConstPack.ops.h" // const_pack == const_pack

using namespace meta17;

template<int...>
struct MyValues {};

static_assert(count_template_values<MyValues<1, 2, 3>> == 3);

static_assert(head_template_values<MyValues<1, 2, 3>> == 1);

static_assert(same<TailTemplateValues<MyValues<1, 2, 3>>, MyValues<2, 3>>);
